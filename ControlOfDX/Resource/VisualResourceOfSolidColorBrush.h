#pragma once

#include "../ControlOfDX.h"
#include "VisualResource.h"

namespace ControlOfDX
{
    using namespace System;
    using namespace System::Drawing;

    /// <summary>�P�F�u���V���\�[�X�B</summary>
	public ref class VisualResourceOfSolidColorBrush sealed
		: public VisualResource
	{
#pragma region "fields"
	private:
        // �F�����l
        float alpha, red, green, blue;

        // �`�惊�\�[�X
        ID2D1Resource * instance;

#pragma endregion

#pragma region "constructor/destructor"
	public:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="red">�ԐF�����l�B</param>
        /// <param name="green">�ΐF�����l�B</param>
        /// <param name="blue">�F�����l�B</param>
        /// <param name="alpha">���������l�B</param>
		VisualResourceOfSolidColorBrush(String ^ name, int red, int green, int blue, int alpha)
			: VisualResource(name),
              alpha(alpha / 255.0f),
              red(red / 255.0f),
              green(green / 255.0f),
              blue(blue / 255.0f) {}

        /// <summary>�f�X�g���N�^�B</summary>
		~VisualResourceOfSolidColorBrush()
        {
            this->ReleaseInstance();
        }

        /// <summary>�t�@�C�i���C�U�B</summary>
        !VisualResourceOfSolidColorBrush()
        {
            this->~VisualResourceOfSolidColorBrush();
        }

#pragma endregion

#pragma region "methods"
    internal:
        /// <summary>���\�[�X���g�p���鏀�����s���B</summary>
        /// <param name="name">�����_�[�^�[�Q�b�g�B</param>
        void Preparation(ID2D1RenderTarget * renderTarget) override
        {
            if (this->instance == NULL) {
                ID2D1SolidColorBrush * brush;
                D2D1_COLOR_F color = D2D1::ColorF(this->red, this->green, this->blue, this->alpha);
                HRESULT hr = renderTarget->CreateSolidColorBrush(color, &brush);
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
        /// <summary>�F�ݒ��ύX����B</summary>
        /// <param name="color">�ύX����F�B</param>
        void SetColor(Color color)
        {
            this->red = red / 255.0f;
            this->green = green / 255.0f;
            this->blue = blue / 255.0f;

            if (this->instance != NULL) {
                D2D1_COLOR_F clr = D2D1::ColorF(color.R / 255.0f,
                                                color.G / 255.0f,
                                                color.B / 255.0f,
                                                color.A / 255.0f);
                ((ID2D1SolidColorBrush*)this->instance)->SetColor(clr);
            }
        }

        /// <summary>�����x��ύX����B</summary>
        /// <param name="opacity">�����x�i0 �` 255�j�B</param>
        void SetOpacity(int opacity)
        {
            this->alpha = opacity / 255.0f;

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
