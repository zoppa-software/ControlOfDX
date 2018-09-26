#pragma once

#include <vector>
#include "../ControlOfDX.h"
#include "../SingletonFactory.h"
#include "VisualResource.h"
#include "VisualResourceOfGeometry.h"

namespace ControlOfDX
{
    using namespace System;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    /// <summary>�W�I���g���O���[�v���\�[�X�B</summary>
	public ref class VisualResourceOfGeometryGroup
		: public VisualResourceOfGeometry
	{
#pragma region "fields"
	private:
        // �W�I���g��
		ID2D1GeometryGroup * geometry;

#pragma endregion

#pragma region "constructor/destructor"
	public:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="fillMode">���\�[�X���B</param>
        /// <param name="geometries">�O���[�v�Ɋ܂߂�W�I���g�����X�g�B</param>
        VisualResourceOfGeometryGroup(String ^ name,
                                      FillMode fillMode,
                                      IEnumerable<VisualResourceOfGeometry^>^ geometries)
			: VisualResourceOfGeometry(name)
		{
            if (!SingletonFactory::GetDirect2DFactory()) {
                throw gcnew ResourceException("�W�I���g���O���[�v�̍쐬�Ɏ��s���܂���");
            }

            ID2D1GeometryGroup * geo;
            std::vector<ID2D1Geometry*> geos;
            for each (VisualResourceOfGeometry ^ item in geometries) {
                geos.push_back(item->GetGeometry());
            }

            HRESULT hr = SingletonFactory::GetDirect2DFactory()->CreateGeometryGroup((D2D1_FILL_MODE)fillMode, geos.data(), geos.size(), &geo);
			if (SUCCEEDED(hr)) {
				this->geometry = geo;
			}
			else {
                throw gcnew ResourceException("�W�I���g���O���[�v�̍쐬�Ɏ��s���܂���");
			}
		}

        /// <summary>�f�X�g���N�^�B</summary>
        virtual ~VisualResourceOfGeometryGroup()
        {
            if (this->geometry != NULL) {
                this->geometry->Release();
                this->geometry = NULL;
            }
        }

        /// <summary>�t�@�C�i���C�U�B</summary>
		!VisualResourceOfGeometryGroup()
        {
            this->~VisualResourceOfGeometryGroup();
        }

#pragma endregion

#pragma region "methods"
    internal:
        /// <summary>���\�[�X���g�p���鏀�����s���B</summary>
        /// <param name="name">�����_�[�^�[�Q�b�g�B</param>
        void Preparation(ID2D1RenderTarget * renderTarget) override
        {

        }

        /// <summary>��`�W�I���g���̎��̂��擾����B</summary>
        /// <return>��`�W�I���g���B</return>
        ID2D1Geometry * GetGeometry() override {
            return this->geometry;
        }

        /// <summary>Direct2D�̃C���X�^���X���擾����B</summary>
        ID2D1Resource * GetInstance() override
        {
            return this->geometry;
        }

#pragma endregion
	};
}