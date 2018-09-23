#pragma once

#include "../ControlOfDX.h"
#include "VisualResource.h"

namespace ControlOfDX
{
    using namespace System;
    using namespace System::Drawing;
    using namespace System::Drawing::Imaging;

    /// <summary>�r�b�g�}�b�v���\�[�X�B</summary>
    public ref class VisualResourceOfBitmap sealed
        : public VisualResource
    {
#pragma region "fields"
    private:
        // �`��r�b�g�}�b�v
        Bitmap ^    bitmap;

        // Direct2D�r�b�g�}�b�v
        ID2D1Bitmap * d2bitmap;

#pragma endregion

#pragma region "properties"
    public:
        /// <summary>�`�悷��r�b�g�}�b�v��ݒ�A�擾����B</summary>
        property Bitmap ^ Source
        {
            Bitmap ^ get() { return this->bitmap; }
            
            void set(Bitmap ^ bit) {
                if (this->bitmap != nullptr) {
                    delete this->bitmap;
                    this->bitmap = nullptr;
                }
                this->bitmap = (Bitmap^)bit->Clone();

                if (this->d2bitmap != NULL) {
                    this->d2bitmap->Release();
                    this->d2bitmap = NULL;
                }
            }
        }

#pragma endregion

#pragma region "constructor/destructor"
    public:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="bitmap">�`��r�b�g�}�b�v�B</param>
		VisualResourceOfBitmap(String ^ name, Bitmap ^ bitmap)
			: VisualResource(name), d2bitmap(NULL)
		{
            this->Source = bitmap;
        }

        /// <summary>�f�X�g���N�^�B</summary>
		virtual ~VisualResourceOfBitmap()
		{
            if (this->bitmap != nullptr) {
                delete this->bitmap;
                this->bitmap = nullptr;
            }

            if (this->d2bitmap != NULL) {
                this->d2bitmap->Release();
                this->d2bitmap = NULL;
            }
        }

        /// <summary>�t�@�C�i���C�U�B</summary>
        !VisualResourceOfBitmap()
        {
            this->~VisualResourceOfBitmap();
        }

#pragma endregion

#pragma region "methods"
    internal:
        /// <summary>���\�[�X���g�p���鏀�����s���B</summary>
        /// <param name="name">�����_�[�^�[�Q�b�g�B</param>
        void Preparation(ID2D1RenderTarget * renderTarget) override
        {
            if (this->d2bitmap == NULL) {
                // �r�b�g�}�b�v�`��^�[�Q�b�g�̍쐬
                ID2D1BitmapRenderTarget * bitmapTarget = NULL;
                HRESULT hr = renderTarget->CreateCompatibleRenderTarget(
                    D2D1::SizeF((float)this->bitmap->Width, (float)this->bitmap->Height),
                    &bitmapTarget
                );

                ID2D1Bitmap * bitmap = NULL;
                if (SUCCEEDED(hr)) {
                    // �`�悷��r�b�g�}�b�v���擾       
                    hr = bitmapTarget->GetBitmap(&bitmap);

                    if (SUCCEEDED(hr)) {
                        // �`��r�b�g�}�b�v����r�b�g�}�b�v�����擾���A�R�s�[����
                        BitmapData ^ bmpData = this->bitmap->LockBits(System::Drawing::Rectangle(0, 0, this->bitmap->Width, this->bitmap->Height),
                                                                      ImageLockMode::ReadWrite,
                                                                      PixelFormat::Format32bppArgb);
                        D2D1_RECT_U rec = D2D1::RectU(0, 0, this->bitmap->Width, this->bitmap->Height);
                        bitmap->CopyFromMemory(&rec, (void*)bmpData->Scan0, bmpData->Stride);
                        this->bitmap->UnlockBits(bmpData);
                    }

                    // �r�b�g�}�b�v�`��^�[�Q�b�g�̉��
                    bitmapTarget->Release();
                    this->d2bitmap = bitmap;
                }
            }
        }

    internal:
        /// <summary>Direct2D�̃C���X�^���X���擾����B</summary>
        ID2D1Resource * GetInstance() override
        {
            return this->d2bitmap;
        }

#pragma endregion
    };
}