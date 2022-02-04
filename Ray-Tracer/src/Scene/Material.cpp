#include "Material.h"
#include <iostream>
#include <print_helpers.h>

Material::Material(aiMaterial* mat) {
	std::cout << mat->GetName().C_Str() << std::endl;
	for (int i = 0; i < mat->mNumProperties; i++)
	{
		std::cout << mat->mProperties[i]->mKey.C_Str() << ", ";
		switch (mat->mProperties[i]->mType)
		{
		case aiPTI_Float:
			glm::vec4 out(-1);
			memcpy(&out.x, mat->mProperties[i]->mData, mat->mProperties[i]->mDataLength);
			std::cout << out;
			break;
		default:
			break;
		}
		std::cout << std::endl;
		std::string property_name = mat->mProperties[i]->mKey.C_Str();
		if (property_name == "$clr.diffuse") {
			memcpy(&m_Colour.x, mat->mProperties[i]->mData, 3 * sizeof(float));
		}
	}
}
