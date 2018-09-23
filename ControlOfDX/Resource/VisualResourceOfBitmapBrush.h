#pragma once

#include "../ControlOfDX.h"
#include "VisualResource.h"

namespace ControlOfDX
{
    using namespace System;
    using namespace System::Drawing;
    using namespace System::Drawing::Imaging;

    /// <summary>�r�b�g�}�b�v�u���V���\�[�X�B</summary>
    public ref class VisualResourceOfBitmapBrush sealed
        : public VisualResource
    {
#pragma region "inner class"
    public:
        /// <summary>�s�����̈������΂��v���p�e�B�B</summary>
        ref class BitmapBrushProperties
        {
        private:
            // �u���V
            VisualResourceOfBitmapBrush ^ parent;

            // �������΂��ݒ�
            ExtendModeParameter exX, exY;

            // ��ԃ��[�h
            BitmapInterpolationMode mode;

        public:
            /// <summary>�������������΂��ݒ��ݒ�A�擾����B</summary>
            property ExtendModeParameter ExtendModeX {
                ExtendModeParameter get() { return this->exX; }
                void set(ExtendModeParameter val) {
                    this->exX = val;
                    if (this->parent != nullptr && this->parent->instance != NULL) {
                        this->parent->instance->SetExtendModeX((D2D1_EXTEND_MODE)this->exX);
                    }
                }
            }

            /// <summary>�c�����������΂��ݒ��ݒ�A�擾����B</summary>
            property ExtendModeParameter ExtendModeY {
                ExtendModeParameter get() { return this->exY; }
                void set(ExtendModeParameter val) {
                    this->exY = val;
                    if (this->parent != nullptr && this->parent->instance != NULL) {
                        this->parent->instance->SetExtendModeY((D2D1_EXTEND_MODE)this->exY);
                    }
                }
            }

            /// <summary>��ԃ��[�h��ݒ�A�擾����B</summary>
            property BitmapInterpolationMode InterpolationMode {
                BitmapInterpolationMode get() { return this->mode; }
                void set(BitmapInterpolationMode val) {
                    this->mode = val;
                    if (this->parent != nullptr && this->parent->instance != NULL) {
                        this->parent->instance->SetInterpolationMode((D2D1_BITMAP_INTERPOLATION_MODE)this->mode);
                    }
                }
            }

        public:
            /// <summary>�R���X�g���N�^�B</summary>
            BitmapBrushProperties(VisualResourceOfBitmapBrush ^ parent)
                : parent(parent),
                  exX(ExtendModeParameter::EXTEND_MODE_WRAP),
                  exY(ExtendModeParameter::EXTEND_MODE_WRAP),
                  mode(BitmapInterpolationMode::BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR)
            {}
        };

#pragma endregion

#pragma region "fields"
    private:
        // �`�惊�\�[�X
        ID2D1BitmapBrush * instance;

        // �`��r�b�g�}�b�v
        Bitmap ^    bitmap;

        // �z�u���[�h�v���p�e�B
        BitmapBrushProperties ^ properties;

#pragma endregion

#pragma region "properties"
    public:
        /// <summary>�`�悷��r�b�g�}�b�v��ݒ�A�擾����B</summary>
        property Bitmap ^ Source
        {
            Bitmap ^ get() { return this->bitmap; }
            void set(Bitmap ^ bit)
            {
                this->ReleaseInstance();
                this->bitmap = (Bitmap^)bit->Clone();
            }
        }

        /// <summary>�r�b�g�}�b�v��z�u���邽�߂̕s�����̈������΂��v���p�e�B���擾����B</summary>
        property BitmapBrushProperties ^ Properties
        {
            BitmapBrushProperties ^ get() { return this->properties; }
        }

#pragma endregion

#pragma region "constructor/destructor"
    public:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="bitmap">�`��r�b�g�}�b�v�B</param>
		VisualResourceOfBitmapBrush(String ^ name, Bitmap ^ bitmap)
			: VisualResource(name)
		{
            this->Source = bitmap;
            this->properties = gcnew BitmapBrushProperties(this);
        }

        /// <summary>�f�X�g���N�^�B</summary>
		virtual ~VisualResourceOfBitmapBrush()
		{
            if (this->bitmap != nullptr) {
                delete this->bitmap;
                this->bitmap = nullptr;
            }
            this->ReleaseInstance();
        }

        /// <summary>�t�@�C�i���C�U�B</summary>
        !VisualResourceOfBitmapBrush()
        {
            this->~VisualResourceOfBitmapBrush();
        }

#pragma endregion

#pragma region "methods"
    internal:
        /// <summary>���\�[�X���g�p���鏀�����s���B</summary>
        /// <param name="name">�����_�[�^�[�Q�b�g�B</param>
        void Preparation(ID2D1RenderTarget * renderTarget) override
        {
            if (this->instance == NULL) {
                // �r�b�g�}�b�v�`��^�[�Q�b�g�̍쐬
                ID2D1BitmapRenderTarget * bitmapTarget = NULL;
                HRESULT hr = renderTarget->CreateCompatibleRenderTarget(
                    D2D1::SizeF((float)this->bitmap->Width, (float)this->bitmap->Height),
                    &bitmapTarget
                );

                ID2D1BitmapBrush * brush;
                if (SUCCEEDED(hr)) {
                    // �`�悷��r�b�g�}�b�v���擾
                    ID2D1Bitmap * bitmap = NULL;
                    hr = bitmapTarget->GetBitmap(&bitmap);

                    if (SUCCEEDED(hr)) {
                        // �`��r�b�g�}�b�v����r�b�g�}�b�v�����擾���A�R�s�[����
                        BitmapData ^ bmpData = this->bitmap->LockBits(System::Drawing::Rectangle(0, 0, this->bitmap->Width, this->bitmap->Height),
                                                                      ImageLockMode::ReadWrite,
                                                                      PixelFormat::Format32bppArgb);
                        D2D1_RECT_U rec = D2D1::RectU(0, 0, this->bitmap->Width, this->bitmap->Height);
                        bitmap->CopyFromMemory(&rec, (void*)bmpData->Scan0, bmpData->Stride);
                        this->bitmap->UnlockBits(bmpData);
                                    
                        // �r�b�g�}�b�v�u���V���쐬����
                        hr = renderTarget->CreateBitmapBrush(bitmap, 
                                                             D2D1::BitmapBrushProperties((D2D1_EXTEND_MODE)this->properties->ExtendModeX,
                                                                                         (D2D1_EXTEND_MODE)this->properties->ExtendModeY,
                                                                                         (D2D1_BITMAP_INTERPOLATION_MODE)this->properties->InterpolationMode),
                                                             &brush);

                        // �u���V��ێ�����
                        if (SUCCEEDED(hr)) {
                            this->instance = brush;
                        }
                        else {
                            this->instance = NULL;
                        }
                        bitmap->Release();
                    }

                    // �r�b�g�}�b�v�`��^�[�Q�b�g�̉��
                    bitmapTarget->Release();
                }
            }
        }

    internal:
        /// <summary>Direct2D�̃C���X�^���X���擾����B</summary>
        ID2D1Resource * GetInstance() override
        {
            return this->instance;
        }

        /// <summary>�`��C���X�^���X���������B</summary>
        void ReleaseInstance() override
        {
            if (this->instance != NULL) {
                this->instance->Release();
                this->instance = NULL;
            }
        }

    public:
        /// <summary>�����x��ύX����B</summary>
        /// <param name="opacity">�����x�i0 �` 255�j�B</param>
        void SetOpacity(int opacity)
        {
            if (this->instance != NULL) {
                ((ID2D1Brush*)this->instance)->SetOpacity(opacity / 255.0f);
            }
        }

        /// <summary>���W�n�𕽍t�ړ�������B</summary>
        void SetTransform()
        {
            if (this->instance != NULL) {
                ((ID2D1Brush*)this->instance)->SetTransform(D2D1::Matrix3x2F::Identity());
            }
        }

        /// <summary>���W�n�𕽍t�ړ�������B</summary>
        /// <param name="offsetX">X�ړ��ʁB</param>
        /// <param name="offsetY">Y�ړ��ʁB</param>
        void SetTransform(float offsetX, float offsetY)
        {
            if (this->instance != NULL) {
                ((ID2D1Brush*)this->instance)->SetTransform(D2D1::Matrix3x2F::Translation(offsetX, offsetY));
            }
        }

        /// <summary>���W�n�𕽍t�ړ�������B</summary>
        /// <param name="matrix">�ړ��ʃ}�g���b�N�X�B</param>
        void SetTransform(Matrix matrix)
        {
            if (this->instance != NULL) {
                ((ID2D1Brush*)this->instance)->SetTransform(matrix.Convert());
            }
        }

#pragma endregion
    };
}