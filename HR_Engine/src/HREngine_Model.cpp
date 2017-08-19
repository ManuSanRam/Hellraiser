#include "HREngine_Model.h"



namespace HR_SDK
{
	/*!



	*/
	bool		C_Model::Load
	(
		const String& _fileName
	)
	{
		Assimp::Importer importer;
		bool result = false;

		const char* file = _fileName.c_str();

		const aiScene* scene = importer.ReadFile(file, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

		if (scene)
		{
			result = Init(scene, _fileName);
		}

		return result;
	}



	/*!



	*/
	bool		C_Model::Init
	(
		const aiScene*	_scene,
		const String&	_fileName
	)
	{
		m_Meshes.resize(_scene->mNumMeshes);
		m_Materials.resize(_scene->mNumMaterials);

		// Initialize the meshes in the scene one by one
		for (unsigned int i = 0; i < m_Meshes.size(); i++) 
		{
			const aiMesh* paiMesh = _scene->mMeshes[i];
			InitMesh(i, paiMesh);
		}

		return InitMaterials(_scene, _fileName);
	}



	/*!



	/*!
	*/
	void		C_Model::InitMesh
	(
		uint32				_index,
		const aiMesh*		_mesh
	)
	{
		Vector<S_Vertex>	_vertices;
		Vector<uint32>		_indices;


		aiVector3D Zero(0.0f, 0.0f, 0.0f);

		for (unsigned int i = 0; i < _mesh->mNumVertices; i++) 
		{
			const aiVector3D* pPos = &(_mesh->mVertices[i]);
			const aiVector3D* pTexCoord = _mesh->HasTextureCoords(0) ? &(_mesh->mTextureCoords[0][i]) : &Zero;

			S_Vertex Vertex(pPos->x, pPos->y, pPos->z, pTexCoord->x, pTexCoord->y);

			_vertices.push_back(Vertex);
		}

		for (unsigned int i = 0; i < _mesh->mNumFaces; i++) 
		{
			const aiFace& Face = _mesh->mFaces[i];
			
			HR_ASSERTION(Face.mNumIndices == 3);

			_indices.push_back(Face.mIndices[0]);
			_indices.push_back(Face.mIndices[1]);
			_indices.push_back(Face.mIndices[2]);
		}

		C_Mesh* mesh = new C_Mesh();
		
		uint32 matIndex = _mesh->mMaterialIndex;
		
		mesh->Init(matIndex, _vertices, _indices);

		m_Meshes.push_back(mesh);
	}



	/*!
	*/
	bool		C_Model::InitMaterials
	(
		const aiScene*		_scene,
		const String&		_fileName
	)
	{
		for (unsigned int i = 0; i < _scene->mNumMaterials; i++) 
		{
			const aiMaterial* pMaterial = _scene->mMaterials[i];

			//m_Textures[i] = NULL;
			if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) 
			{
				aiString Path;

				if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) 
				{
					//std::string FullPath = Dir + "/" + Path.data;
					//m_Textures[i] = new Texture(GL_TEXTURE_2D, FullPath.c_str());

					//if (!m_Textures[i]->Load()) 
					//{
						//printf("Error loading texture '%s'\n", FullPath.c_str());
						//delete m_Textures[i];
						//m_Textures[i] = NULL;
						//Ret = false;
					}
				}
			}

			//return Ret;
		}
	}



	/*!
	*/
	void C_Model::Render
	(

	)
	{

	}



	/*!



	*/
	void C_Model::Close
	(

	)
	{

	}
}