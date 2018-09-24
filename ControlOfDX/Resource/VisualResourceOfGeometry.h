#pragma once

#include <vector>
#include "../ControlOfDX.h"
#include "VisualResource.h"

namespace ControlOfDX
{
    /// <summary>�W�I���g�����\�[�X�C���^�[�t�F�[�X�B</summary>
    public ref class VisualResourceOfGeometry abstract
        : VisualResource
	{
#pragma region "constructor/destructor"
    public:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="name">���\�[�X���B</param>
        VisualResourceOfGeometry(String ^ name)
            : VisualResource(name)
        {}

        /// <summary>�f�X�g���N�^�B</summary>
        virtual ~VisualResourceOfGeometry() {}

        /// <summary>�t�@�C�i���C�U�B</summary>
        !VisualResourceOfGeometry() {}

#pragma endregion

#pragma region "methods"
    internal:
        /// <summary>�W�I���g���̎��̂��擾����B</summary>
        /// <return>�W�I���g���B</return>
        virtual ID2D1Geometry * GetGeometry() = 0;

#pragma endregion

	};
}
