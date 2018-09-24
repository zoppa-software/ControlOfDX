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

    /// <summary>�p�X�W�I���g�����\�[�X�B</summary>
	public ref class VisualResourceOfPathGeometry
		: public VisualResourceOfGeometry
	{
#pragma region "fields"
	private:
        // �p�X�W�I���g��
		ID2D1PathGeometry * geometry;

#pragma endregion

#pragma region "constructor/destructor"
	public:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="factory">�����_�[�t�@�N�g���B</param>
		VisualResourceOfPathGeometry(String ^ name)
			: VisualResourceOfGeometry(name)
		{
            if (!SingletonFactory::GetDirect2DFactory()) {
                throw gcnew ResourceException("�p�X�W�I���g���̍쐬�Ɏ��s���܂���");
            }

			ID2D1PathGeometry * geo;
			HRESULT hr = SingletonFactory::GetDirect2DFactory()->CreatePathGeometry(&geo);
			if (SUCCEEDED(hr)) {
				this->geometry = geo;
			}
			else {
				throw gcnew ResourceException("�p�X�W�I���g���̍쐬�Ɏ��s���܂���");
			}
		}

        /// <summary>�f�X�g���N�^�B</summary>
        virtual ~VisualResourceOfPathGeometry()
        {
            if (this->geometry != NULL) {
                this->geometry->Release();
                this->geometry = NULL;
            }
        }

        /// <summary>�t�@�C�i���C�U�B</summary>
        !VisualResourceOfPathGeometry()
        {
            this->~VisualResourceOfPathGeometry();
        }

#pragma endregion

#pragma region "methods"
	public:
        /// <summary>�W�I���g���V���N���쐬����B</summary>
        /// <return>�W�I���g���V���N�B</return>
		GeometrySink ^ CreateGeometrySink()
		{
			ID2D1GeometrySink * sink;
			HRESULT hr = this->geometry->Open(&sink);
			if (SUCCEEDED(hr)) {
				return gcnew GeometrySink(sink);
			}
			else {
				throw gcnew ResourceException("�W�I���g���V���N�̍쐬�Ɏ��s���܂���");
			}
		}

    internal:
        /// <summary>���\�[�X���g�p���鏀�����s���B</summary>
        /// <param name="name">�����_�[�^�[�Q�b�g�B</param>
        void Preparation(ID2D1RenderTarget * renderTarget) override
        {

        }

        /// <summary>�p�X�W�I���g���̎��̂��擾����B</summary>
        /// <return>�p�X�W�I���g���B</return>
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
