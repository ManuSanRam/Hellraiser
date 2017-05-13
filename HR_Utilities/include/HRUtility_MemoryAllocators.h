#pragma once

#undef min
#undef max

#include <new>
#include <atomic>
#include <limits>
#include <utility>

/*!***********************************************************************************************************************************************************
 * @file		HRUtility_MemoryAllocators.h
 *
 * This file contains the declaration of different memory allocators, used to reserve memory spaces exclusive for variables of certain size.
 * The memory allocators and its allocation methods are as follows:
 * - Standard allocator.
 *     Allocates memory in a linear way. This method could lead to memory fragmentation, since any deallocation is made out of order.
 * - Stack allocator.
 *     Allocates blocks of memory in a stack-contained method. Allocator keeps track of the position of the last allocated memory block
 *     so any new allocations are reserved after that point. For deallocations, the last reserved blocked is deallocated first. Any 
 *     future deallocations follow this order.
 * - Frame allocator.
 *     Allocates blocks of memory to save data used in a single frame of the app. Once the frame's lifetime is over, any allocations made
 *     in said frame are deallocated.
 * - Pool allocator.
 *     Reserves memory blocks in a circular method, deallocating memory from the start of the memory and allocating memory from that point
 *     for any future allocations.
 *
 * @date        03-10-2016
 * @author		Manuel Aldair Santos Ramón (ManuSanRam)
 * @copyright	Infernal Coders S.A.
*************************************************************************************************************************************************************/

namespace HR_SDK
{
	/*!*/
	class C_MemoryAllocatorBase;

	/*!*/
	class C_MemoryCounter
	{
	public:
		/*!*/
		static HR_UTILITY_EXPORT uint64 GetNumberAllocations()
		{
			/*!*/
			return m_Allocations;
		}

		/*!*/
		static HR_UTILITY_EXPORT uint64 GetNumberFrees()
		{
			/*!*/
			return m_Frees;
		}

	private:
		/*!*/
		friend class C_MemoryAllocatorBase;

		/*!*/
		static HR_UTILITY_EXPORT void IncrementAllocationCount()
		{
			/*!*/
			m_Allocations++;
		}

		/*!*/
		static HR_UTILITY_EXPORT void IncrementFreeCount()
		{
			/*!*/
			m_Frees++;
		}

		/*!*/
		static HR_THREAD_LOCAL uint64 m_Allocations;
		/*!*/
		static HR_THREAD_LOCAL uint64 m_Frees;
	};

	/*!*/
	template<class T>
	class C_MemoryAllocator
	{
	public:
		/*!*/
		static inline void* Allocate(SIZE_T prm_Bytes)
		{
          #if HR_PROFILER_ENABLED  //!
            IncrementAllocationCount();  //!
          #endif  //!
		  return malloc(prm_Bytes);  //!
		}

		/*!*/
		static inline void* AllocateArray(SIZE_T prm_Bytes, uint32 prm_Count)
		{
          #if HR_PROFILER_ENABLED  //!
            IncrementAllocationCount();  //!
          #endif
		  return malloc(prm_Bytes * prm_Count);  //!
		}

		/*!*/
		static inline void Free(void* prm_Ptr)
		{
          #if HR_PROFILING_ENABLED
            IncrementFreeCount();
          #endif
	      ::free(prm_Ptr);
		}

		/*!*/
		static inline void FreeArray(void* prm_Ptr, uint32 prm_Count)
		{
		  HR_UNREFERENCED_PARAMETER(prm_Count);
          #if HR_PROFILING_ENABLED
            IncrementFreeCount();
          #endif
		  ::free(prm_Count);
		}
	};

	/*!
	*/
	class C_GenAllocator
	{};

	/*!
	*/
	template<class Allocator>
	inline void* hr_allocate(SIZE_T prm_Count)
	{
		return C_MemoryAllocator<Allocator>::Allocate(prm_Count);
	}

	/*!
	*/
	template<class T, class Allocator>
	inline T* hr_allocate()
	{
		return(T*)C_MemoryAllocator<Allocator>::Allocate(sizeof(T));
	}

	/*!
	*/
	template<class T, class Allocator>
	inline T* hr_newN(uint32 prm_Count)
	{
		T* Ptr = (T*)C_MemoryAllocator<Allocator>::AllocateArray(sizeof(T), prm_Count);

		for (uint32 i = 0; i < prm_Count; i++)
		{
			new((void*)&Ptr[i]) T;
		}

		return Ptr;

	}

	/*!
	*/
	template<class Type, class Allocator, class...Args>
	Type* hr_new(Args&&... args)
	{
		return new(hr_allocate<Allocator>(sizeof(Type))) Type std::forward<Args>(args)...;
	}

	/*!
	*/
	template<class Allocator>
	inline void hr_free(void* prm_Ptr)
	{
		C_MemoryAllocator<Allocator>::Free(prm_Ptr);
	}

	/*!
	*/
	template<class Type, class Allocator = C_GenAllocator>
	inline void hr_delete(Type* prm_Ptr)
	{
		(prm_Ptr)->~Type();
		C_MemoryAllocator<Allocator>::Free(prm_Ptr);
	}

	/*!
	*/
	template<class Type, class Allocator = C_GenAllocator>
	inline void hr_deleteN(Type* prm_Ptr, uint32 prm_Count)
	{
		for (uint32 i = 0; i < prm_Count; i++)
		{
			prm_Ptr[i].~Type();
		}

		C_MemoryAllocator<Allocator>::Free(prm_Ptr, prm_Count);

	}

	/*!
	*/
	inline void* hr_allocate(SIZE_T prm_Count)
	{
		return C_MemoryAllocator<C_GenAllocator>::Allocate(prm_Count);
	}

	/*!
	 * @brief Allocates a single block of memory of type Type
	 * @return Pointer to the allocated memory block
	*/
	template<class Type>
	inline Type* hr_allocate()
	{
		return (Type*)C_MemoryAllocator<C_GenAllocator>::Allocate(sizeof(Type));
	}

	/*!
	 * @brief Dynamiclly allocates memory for nth number of types inside of the RAM
	 * @param prm_Count Number of memory blocks to be allocated inside the memory.
	 * @return Pointer to the allocated memory 
	*/
	template<class Type>
	inline Type* hr_newN(uint32 prm_Count)
	{
		//! Allocates 'n' number of memory using method allocate inside Ptr of type Type 
		Type* Ptr = (Type*)C_MemoryAllocator<C_GenAllocator>::Allocate(sizeof(Type) * prm_Count);

		//! Iterates through the number of allocations made
		for (uint32 i = 0; i < prm_Count; i++)
		{
			//! Dynamiclly creates memory for objects
			new ((void*)&Ptr[i]) Type;
		}

		//! Returns pointer to blocks
		return Ptr;

	}

	/*!
	 * @brief Dynamiclly allocates memory for a complex object, taking any arguments necessary to create said object
	 * @param args Arguments necessary for the correct construction of the object.
	*/
	template<class Type, class... Args>
	Type* hr_new(Args&&... args)
	{
		return new (hr_allocate<C_GenAllocator>(sizeof(Type))) Type(std::forward<Args>(args));
	}

	/*!
	*/
	inline void hr_free(void* Ptr)
	{
		C_MemoryAllocator<C_GenAllocator>::Free(Ptr);
	}
}

	/*!
	*/
    #define HR_PVT_DELETE(Type, Ptr)  \
                 (Ptr)->~Type();  \
	             HR_SDK::C_MemoryAllocator<HR_SDK::C_GenAllocator>::Free(Ptr);

	/*!
	*/
    #define HR_PVT_DELETE_A(Type, Ptr, Allocator)   \
                              (Ptr)->~Type()    \
                              HR_SDK::C_MemoryAllocator<HR_SDK::Allocator>::free(Ptr);


namespace HR_SDK
{
	/*!
	 * @brief Declares a stack-based memory allocator.
	 * This memory allocator stacks up memory blocks in an order, and deallocates said blocks in the reverse order they arrived to the stack
	*/
	template<class Type, class Allocator = C_GenAllocator>
	class C_StdAlloc 
	{
	public:
		/*!
		 * @brief Type allocated inside of the stack.
		*/
		typedef Type value_type;
		
		/*!
		 * @brief Constructor 
		*/
		C_StdAlloc() _NOEXCEPT {}

		template <class Type, class Allocator>
		C_StdAlloc(const C_StdAlloc<Type, Allocator>&) _NOEXCEPT {}

		/*!
		 * @brief Compare of two standard allocators
		 * @param Reference to a standard allocator.
		 * @return Returns whether both allocators are different or not
		*/
		template<class Type, class Allocator>
		bool operator ==(const C_StdAlloc<Type, Allocator>&) const _NOEXCEPT
		{
			return true;
		}

		/*!
		 * @brief Compare of two standard allocators
		 * @param Reference to a standard allocator.
		 * @return Returns whether both allocators are different or not
		*/
		template<class Type, class Allocator>
		bool operator !=(const C_StdAlloc<Type, Allocator>&) const _NOEXCEPT
		{
			return false;
		}

		/*!
		 * @brief Allocates n number of blocks of memory, each of size of Type.
		 * @param prm_Num Number of blocks to be allocated
		 * @return Pointer to the allocated memory space
		*/
		Type* allocate(const size_t prm_Num) const
		{
			if (prm_Num == 0)  //! Check if number is valid (non zero)
			{
				return nullptr;  //! If zero, return a null pointer, and finish function
			}

			if (prm_Num > static_cast<SIZE_T>(-1) / sizeof(Type))  //! Check if size is correct (Not to low, nor to high)
			{
				throw std::bad_array_new_length();  //! Return a bad length exception, meaning length is incorrect, and end function
			}

			void* const PV = hr_allocate<Allocator>((uint32)(prm_Num * sizeof(Type)));  //! Allocation of memory block, of size Type is made

			if (!PV)  //! Check if memory block was successfully allocated
			{
				throw std::bad_alloc();  //! If not, the allocation return a bad_alloc exception
			}

			return static_cast<Type*>(PV);  //! If allocation was successfully made, return 
		}

		/*!*/
		void deallocate(Type* _Ptr, size_t) const _NOEXCEPT
		{
			hr_free<Allocator>(_Ptr);
		}
	};

	/*!
	 * @class C_StackAlloc
	 * @brief Allocates blocks of memory of certain Type size in memory utilizing a stack-based method
	 * Stack-based method (Last In First Out), allocates memory from bottom to top of stack, any deallocation is made in reverse
	*/
	template<class Type, class Allocator = C_GenAllocator>
	class C_StackAlloc
	{
	public:
		/*!
		 * @brief Defaullt constructor
		*/
		C_StackAlloc() : mp_Start(0), mp_Pos(mp_Start), mp_End(mp_Pos) _NOEXCEPT
		{

		}

		/*!
		 * @brief Destructor
		*/
		~C_StackAlloc()
		{
			free(mp_Start);
		}

		/*!
		 * @brief Points to the start of the stack.
		*/
		uint8* mp_Start;
		
		/*!
		 * @brief Points to the last memory space an allocation can be made, marks also the point where a new allocation can be made
		*/
		uint8* mp_End;

		/*!
		 * @brief Points to the current position of the stack.
		 * It's the only pointer that changes, IS THIS NECESSARY??
		 * Belieave so to keep track of how many blovks of type Type have been allocated before memory runs out
		*/
		uint8* mp_Pos;

		void InitStack(SIZE_T prm_Size)
		{
			mp_Start = malloc(prm_Size);
			mp_Pos = mp_Start;
			mp_End = mp_Start + prm_Size;
		}

		/*!
		 * @brief Allocates a memory block of size of Type in memory
		 * @param prm_Count Number of blocks of size of Type to allocate
		 * @return The value of the allocated block 
		*/
		Type* allocate(uint32 prm_Count)
		{
			Type* returnPtr = nullptr;  //! This return pointer returns the reference of the allocated memory block

			if (prm_Count == 0)  //! If we pass a zero, meaning to allocate nothing
			{//! Zero has been passed so there's no allocations requested
				return nullptr;  // We return a reference to a null pointer (Pointing to zero address)
			}

			if (prm_Count > static_cast<SIZE_T>(-1) / sizeof(Type))  //! If the length is incorrect (either negative number or greater than allocations)
			{//! Length is not valid (Either too small or too long)
				throw std::bad_array_new_length();  //! If we passed and incorrect length (Access violation), we pass an exception of bad length
			}

			if (sizeof(Type) * prm_Count < mp_End - mp_Pos)  //! Check if the current position has not reached the end/top of the stack
			{//! By pointer arithm. the current position has not reached the end.
				returnPtr = mp_Pos;  //! Set the current allocation at the last allocated position
				mp_Pos += sizeof(Type) * prm_Count;  //! The last allocated position is changed to the current last allocated position
			}

			return static_cast<Type*>(returnPtr);  //! If allocation was successfully made, return value of the allocated block
		}//! END OF FUNCTION

		/*!
		 * @brief Deallocates "n" number of blocks of size of Type
		 * @param prm_Count Number of "n" blocks of memory allocated in memory that are to be allocated
		 * The number of blocks start counting from the last allocated block down to the begonning of the block
		*/
		void deallocate()
		{

		}//! END OF FUNCTION

		/*!
		 * @brief Resets the position if the stack to the start
		*/
		void Reset()
		{
			//! Set position back to the start of the stack
			mp_Pos = mp_Start;
		}
	};

	template<class Type, class Allocator = C_GenAllocator>
	class C_FrameAlloc
	{
	public:
		Type* allocate(void* prm_Data, uint32 prm_Count)
		{

		}

		void deallocate(uint32 prm_Count)
		{

		}
	};

	template<class Type, class Allocator = C_GenAllocator>
	class C_PoolAlloc
	{
	public:
		Type* allocate(void* prm_Data, uint32 prm_Count)
		{

		}

		void deallocate(uint32 prm_Count)
		{

		}
	};

}