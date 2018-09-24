#pragma once

#include "../ControlOfDX.h"
#include "../SingletonFactory.h"
#include "VisualResource.h"
#include "VisualResourceOfGeometry.h"
#include "VisualResourceOfPathGeometry.h"
#include "VisualResourceOfRectangleGeometry.h"

namespace ControlOfDX
{
    using namespace System;
    using namespace System::Drawing;

    /// <summary>�ό`�W�I���g�����\�[�X�B</summary>
	public ref class VisualResourceOfTransformedGeometry
		: public VisualResourceOfGeometry
	{
#pragma region "fields"
	private:
        // �W�I���g��
		ID2D1TransformedGeometry * geometry;

#pragma endregion

#pragma region "constructor/destructor"
	public:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="geometry">�W�I���g���B</param>
        /// <param name="matrix">�ό`�ʁB</param>
		VisualResourceOfTransformedGeometry(String ^ name,
                                            VisualResourceOfGeometry ^ geometry,
                                            Matrix matrix)
			: VisualResourceOfGeometry(name)
		{
            if (!SingletonFactory::GetDirect2DFactory()) {
                throw gcnew ResourceException("�ό`�W�I���g���̍쐬�Ɏ��s���܂���");
            }

			ID2D1TransformedGeometry * geo;
			HRESULT hr = SingletonFactory::GetDirect2DFactory()->CreateTransformedGeometry(geometry->GetGeometry(), matrix.Convert(), &geo);
			if (SUCCEEDED(hr)) {
				this->geometry = geo;
			}
			else {
                throw gcnew ResourceException("�ό`�W�I���g���̍쐬�Ɏ��s���܂���");
			}
		}

        /// <summary>�f�X�g���N�^�B</summary>
        virtual ~VisualResourceOfTransformedGeometry()
        {
            if (this->geometry != NULL) {
                this->geometry->Release();
                this->geometry = NULL;
            }
        }

        /// <summary>�t�@�C�i���C�U�B</summary>
        !VisualResourceOfTransformedGeometry()
        {
            this->~VisualResourceOfTransformedGeometry();
        }

#pragma endregion

#pragma region "methods"
    internal:
        /// <summary>���\�[�X���g�p���鏀�����s���B</summary>
        /// <param name="name">�����_�[�^�[�Q�b�g�B</param>
        void Preparation(ID2D1RenderTarget * renderTarget) override
        {

        }

        /// <summary>�ό`�W�I���g���̎��̂��擾����B</summary>
        /// <return>�ό`�W�I���g���B</return>
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