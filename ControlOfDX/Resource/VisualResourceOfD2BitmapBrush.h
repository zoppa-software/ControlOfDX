#pragma once

#include "../ControlOfDX.h"
#include "VisualResource.h"

namespace ControlOfDX
{
    using namespace System;
    using namespace System::Drawing;
    using namespace System::Drawing::Imaging;

    /// <summary>�r�b�g�}�b�v�u���V���\�[�X�B</summary>
    public ref class VisualResourceOfD2BitmapBrush sealed
        : public VisualResource
    {
#pragma region "inner class"
    public:
        /// <summary>�s�����̈������΂��v���p�e�B�B</summary>
        ref class BitmapBrushProperties
        {
        private:
            // �������΂��ݒ�
            ExtendModeParameter exX, exY;

            // ��ԃ��[�h
            BitmapInterpolationMode mode;

        public:
            /// <summary>�������������΂��ݒ��ݒ�A�擾����B</summary>
            property ExtendModeParameter ExtendModeX {
                ExtendModeParameter get() { return this->exX; }
                void set(ExtendModeParameter val) { this->exX = val; }
            }

            /// <summary>�c�����������΂��ݒ��ݒ�A�擾����B</summary>
            property ExtendModeParameter ExtendModeY {
                ExtendModeParameter get() { return this->exY; }
                void set(ExtendModeParameter val) { this->exY = val; }
            }

            /// <summary>��ԃ��[�h��ݒ�A�擾����B</summary>
            property BitmapInterpolationMode InterpolationMode {
                BitmapInterpolationMode get() { return this->mode; }
                void set(BitmapInterpolationMode val) { this->mode = val; }
            }

        public:
            /// <summary>�R���X�g���N�^�B</summary>
            BitmapBrushProperties()
                : exX(ExtendModeParameter::EXTEND_MODE_WRAP),
                exY(ExtendModeParameter::EXTEND_MODE_WRAP),
                mode(BitmapInterpolationMode::BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR)
            {}
        };

#pragma endregion

#pragma region "fields"
    private:
        // �`�惊�\�[�X
        ID2D1Resource * instance;

        // �`��r�b�g�}�b�v
        VisualResourceOfBitmap ^ bitmap;

        // �z�u���[�h�v���p�e�B
        BitmapBrushProperties ^ properties;

#pragma endregion

#pragma region "properties"
    public:
        /// <summary>�`�悷��r�b�g�}�b�v��ݒ�A�擾����B</summary>
        property Bitmap ^ Source
        {
            Bitmap ^ get() { return this->bitmap->Source; }
            void set(Bitmap ^ bit) {
                this->ReleaseInstance();
                this->bitmap->Source = (Bitmap^)bit->Clone();
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
        VisualResourceOfD2BitmapBrush(String ^ name, VisualResourceOfBitmap ^ bitmap)
            : VisualResource(name), bitmap(bitmap)
        {
            this->properties = gcnew BitmapBrushProperties();
        }

        /// <summary>�f�X�g���N�^�B</summary>
        virtual ~VisualResourceOfD2BitmapBrush()
        {
            this->ReleaseInstance();
        }

        /// <summary>�t�@�C�i���C�U�B</summary>
        !VisualResourceOfD2BitmapBrush()
        {
            this->~VisualResourceOfD2BitmapBrush();
        }

#pragma endregion

#pragma region "methods"
    internal:
        /// <summary>���\�[�X���g�p���鏀�����s���B</summary>
        /// <param name="name">�����_�[�^�[�Q�b�g�B</param>
        void Preparation(ID2D1RenderTarget * renderTarget) override
        {
            HRESULT hr;
            ID2D1BitmapBrush * brush;

            if (this->instance == NULL) {
                // �r�b�g�}�b�v�u���V���쐬����
                hr = renderTarget->CreateBitmapBrush((ID2D1Bitmap*)bitmap->GetInstance(),
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