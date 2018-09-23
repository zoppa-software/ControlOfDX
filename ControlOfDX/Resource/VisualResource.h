#pragma once

#include "../ControlOfDX.h"

namespace ControlOfDX
{
    using namespace System;
    using namespace System::Drawing;

    /// <summary>���\�[�X�N���X�B</summary>
	public ref class VisualResource abstract
		: IDisposable
	{
#pragma region "fields"
	private:
		/// <summary>���\�[�X���B</summary>
        String ^ name;

#pragma endregion

#pragma region "constructor/destructor"
	protected:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="name">���\�[�X���B</param>
		VisualResource(String ^ name)
			: name(name)
		{}

        /// <summary>�f�X�g���N�^�B</summary>
		virtual ~VisualResource() {}

        /// <summary>�t�@�C�i���C�U�B</summary>
		!VisualResource() {
			this->~VisualResource();
		}

    public:
        /// <summary>���\�[�X�����擾����B</summary>
        property String ^ Name {
            String ^ get() { return this->name; }
        }

        /// <summary>�f�o�C�X�ˑ����\�[�X�Ȃ�ΐ^��Ԃ��B</summary>
        property virtual bool IsDependent {
            bool get() { return false; }
        }

#pragma endregion

#pragma region "methods"
	public:
        /// <summary>����������s���B</summary>
        /// <param name="obj">��r�ΏہB</param>
        /// <return>��������ΐ^�B</return>
		bool Equals(Object ^ obj) override {
			if (this->GetType()->IsInstanceOfType(obj)) {
				return this->name == ((VisualResource^)obj)->name;
			}
			else {
				return false;
			}
		}

        /// <summary>�n�b�V���R�[�h���擾����B</summary>
        /// <return>�n�b�V���R�[�h�l�B</return>
		int GetHashCode() override {
			return this->name->GetHashCode();
		}

    internal:
        /// <summary>�摜���\�[�X���g�p���鏀�����s���B</summary>
        /// <param name="name">�����_�[�^�[�Q�b�g�B</param>
        virtual void PreparationImage(ID2D1RenderTarget * renderTarget) {};

        /// <summary>���\�[�X���g�p���鏀�����s���B</summary>
        /// <param name="name">�����_�[�^�[�Q�b�g�B</param>
        virtual void Preparation(ID2D1RenderTarget * renderTarget) = 0;

	internal:
        /// <summary>Direct2D�̃C���X�^���X���擾����B</summary>
        virtual ID2D1Resource * GetInstance() { return NULL; }

        /// <summary>�R���C���^�[�t�F�C�X�̃C���X�^���X���擾����B</summary>
        virtual IUnknown * GetWriteInstance() { return NULL; }

        /// <summary>�`��C���X�^���X���������B</summary>
        virtual void ReleaseInstance() {}

#pragma endregion
	};
}

