#pragma once

#include "../ControlOfDX.h"
#include "../SingletonFactory.h"
#include "VisualResource.h"
#include "VisualResourceOfGeometry.h"

namespace ControlOfDX
{
    using namespace System;
    using namespace System::Drawing;

    /// <summary>��`�W�I���g�����\�[�X�B</summary>
	public ref class VisualResourceOfRectangleGeometry
		: public VisualResourceOfGeometry
	{
#pragma region "fields"
	private:
        // �W�I���g��
		ID2D1RectangleGeometry * geometry;

#pragma endregion

#pragma region "constructor/destructor"
	public:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="rectangle">�Ώۋ�`�B</param>
		VisualResourceOfRectangleGeometry(String ^ name,
                                          RectangleF rectangle)
			: VisualResourceOfGeometry(name)
		{
            if (!SingletonFactory::GetDirect2DFactory()) {
                throw gcnew ResourceException("��`�W�I���g���̍쐬�Ɏ��s���܂���");
            }

            D2D1_RECT_F rec = D2D1::RectF(rectangle.Left,
                                          rectangle.Top,
                                          rectangle.Right,
                                          rectangle.Bottom);
			ID2D1RectangleGeometry * geo;
			HRESULT hr = SingletonFactory::GetDirect2DFactory()->CreateRectangleGeometry(rec, &geo);
			if (SUCCEEDED(hr)) {
				this->geometry = geo;
			}
			else {
                throw gcnew ResourceException("��`�W�I���g���̍쐬�Ɏ��s���܂���");
			}
		}

        /// <summary>�f�X�g���N�^�B</summary>
        virtual ~VisualResourceOfRectangleGeometry()
        {
            if (this->geometry != NULL) {
                this->geometry->Release();
                this->geometry = NULL;
            }
        }

        /// <summary>�t�@�C�i���C�U�B</summary>
		!VisualResourceOfRectangleGeometry()
        {
            this->~VisualResourceOfRectangleGeometry();
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