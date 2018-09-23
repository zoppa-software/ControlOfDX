#pragma once

#include <vector>
#include "../ControlOfDX.h"
#include "VisualResource.h"

namespace ControlOfDX
{
    using namespace System;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    /// <summary>���˃O���f�[�V�����u���V�C���X�^���X�B</summary>
	public ref class VisualResourceOfRadialGradientBrush sealed
        : public VisualResource
    {
#pragma region "inner class"
    public:
        /// <summary>�O���f�[�V�������E�̈ʒu�ƐF���i�[����B</summary>
        ref class GradientStop
        {
        private:
            // �F
            Color color;

            // �ʒu
            float position;

        public:
            /// <summary>�F�ݒ��ݒ�A�擾����B</summary>
            property Color GradientColor {
                Color get() { return this->color; }
                void set(Color val) { this->color = val; }
            }

            /// <summary>�ʒu�ݒ��ݒ�A�擾����B</summary>
            property float Position {
                float get() { return this->position; }
                void set(float val) { this->position = val; }
            }

        public:
            /// <summary>�R���X�g���N�^�B</summary>
            /// <param name="edgeColor">�F�B</param>
            /// <param name="position">�ʒu�B</param>
            GradientStop(Color edgeColor, float position)
                : color(edgeColor), position(position)
            {}
        };

        /// <summary>�O���f�[�V�����̌��_�̃I�t�Z�b�g�A�O���f�[�V�����ȉ~�̃T�C�Y�ƈʒu���i�[�B</summary>
        ref class RadialGradientBrushProperties
        {
        private:
            // �O���f�[�V�����ȉ~�̒��S
            PointF  center;

            // �O���f�[�V�����ȉ~�̒��S�Ƒ��ΓI�ȃO���f�[�V�������_�̃I�t�Z�b�g
            PointF  gradientOriginOffset;

            // �O���f�[�V�����ȉ~��X���a
            float   radiusX;

            // �O���f�[�V�����ȉ~��Y���a
            float   radiusY;

        public:
            /// <summary>�O���f�[�V�����ȉ~�̒��S��ݒ�A�擾����B</summary>
            property PointF Center {
                PointF get() { return this->center; }
                void set(PointF pos) { this->center = pos; }
            }

            /// <summary>�O���f�[�V�����ȉ~�̒��S�Ƒ��ΓI�ȃO���f�[�V�������_�̃I�t�Z�b�g��ݒ�A�擾����B</summary>
            property PointF GradientOriginOffset {
                PointF get() { return this->gradientOriginOffset; }
                void set(PointF pos) { this->gradientOriginOffset = pos; }
            }

            /// <summary>�O���f�[�V�����ȉ~��X���a��ݒ�A�擾����B</summary>
            property float RadiusX {
                float get() { return this->radiusX; }
                void set(float pos) { this->radiusX = pos; }
            }

            /// <summary>�O���f�[�V�����ȉ~��Y���a��ݒ�A�擾����B</summary>
            property float RadiusY {
                float get() { return this->radiusY; }
                void set(float pos) { this->radiusY = pos; }
            }
        };

#pragma endregion

#pragma region "fields"
	private:
        // �`�惊�\�[�X
        ID2D1Resource * instance;

        // �O���f�[�V�������E�̈ʒu�ƐF���X�g
        List<GradientStop^>^ gradientStops;

        // �K���}�F���
        GammaParameter gamma;

        // �F�̈������΂��ݒ�
        ExtendModeParameter extendMode;

        // �O���f�[�V�����̌��_�̃I�t�Z�b�g�A�O���f�[�V�����ȉ~�̃T�C�Y�ƈʒu
        RadialGradientBrushProperties ^ properties;

#pragma endregion

#pragma region "properties"
    public:
        /// <summary>�K���}�F��Ԑݒ��ݒ�A�擾����B</summary>
        property GammaParameter Gamma {
            GammaParameter get() { return this->gamma; }
            void set(GammaParameter gamma) { this->gamma = gamma; }
        }

        /// <summary>�F�̈������΂��ݒ��ݒ�A�擾����B</summary>
        property ExtendModeParameter ExtendMode {
            ExtendModeParameter get() { return this->extendMode; }
            void set(ExtendModeParameter mode) { this->extendMode = mode; }
        }

        /// <summary>�O���f�[�V�����̌��_�̃I�t�Z�b�g�A�O���f�[�V�����ȉ~�̃T�C�Y�ƈʒu��ݒ�A�擾����B</summary>
        property RadialGradientBrushProperties ^ Propertes {
            RadialGradientBrushProperties ^ get() { return this->properties; }
        }

#pragma endregion

#pragma region "constructor/destructor"
	public:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="name">���\�[�X���B</param>
		VisualResourceOfRadialGradientBrush(String ^ name)
			: VisualResource(name),
              gamma(GammaParameter::GAMMA_2_2),
              extendMode(ExtendModeParameter::EXTEND_MODE_CLAMP)
        {
            this->gradientStops = gcnew List<GradientStop^>();
            this->properties = gcnew RadialGradientBrushProperties();
        }

        /// <summary>�f�X�g���N�^�B</summary>
		~VisualResourceOfRadialGradientBrush()
        {
            this->ReleaseInstance();
        }

        /// <summary>�t�@�C�i���C�U�B</summary>
        !VisualResourceOfRadialGradientBrush()
        {
            this->~VisualResourceOfRadialGradientBrush();
        }

#pragma endregion

#pragma region "methods"
	public:
        /// <summary>�O���f�[�V�������E�̈ʒu�ƐF��S�ď�������B</summary>
        void ClearGradientStops()
        {
            this->gradientStops->Clear();
        }

        /// <summary>�O���f�[�V�������E�̈ʒu�ƐF��ǉ�����B</summary>
        void AddGradientStop(Color edgeColor, float position)
        {
            this->gradientStops->Add(gcnew GradientStop(edgeColor, position));
        }

        /// <summary>���\�[�X���g�p���鏀�����s���B</summary>
        /// <param name="name">�����_�[�^�[�Q�b�g�B</param>
        void Preparation(ID2D1RenderTarget * renderTarget) override
        {
            if (this->instance == NULL) {
                // �O���f�[�V�������E�̈ʒu�ƐF�����X�g������
                std::vector<D2D1_GRADIENT_STOP> pos;
                if (this->gradientStops->Count > 0) {
                    for each (GradientStop^ stp in this->gradientStops) {
                        D2D1_GRADIENT_STOP st;
                        st.color = D2D1::ColorF(stp->GradientColor.R / 255.0f,
                                                stp->GradientColor.G / 255.0f,
                                                stp->GradientColor.B / 255.0f,
                                                stp->GradientColor.A / 255.0f);
                        st.position = stp->Position;
                        pos.push_back(st);
                    }
                }
                else {
                    D2D1_GRADIENT_STOP st;
                    st.color = D2D1::ColorF(1, 1, 1, 1);
                    st.position = 1;
                    pos.push_back(st);
                }

                // �O���f�[�V�����ݒ���s��
                ID2D1GradientStopCollection * gradientStops = NULL;
                ID2D1RadialGradientBrush * brush = NULL;
                HRESULT hr = renderTarget->CreateGradientStopCollection(pos.data(),
                                                                        (UINT32)pos.size(),
                                                                        (D2D1_GAMMA)this->gamma,
                                                                        (D2D1_EXTEND_MODE)this->extendMode,
                                                                        &gradientStops);
                if (SUCCEEDED(hr)) {
                    D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES props = D2D1::RadialGradientBrushProperties(
                        D2D1::Point2F(this->properties->Center.X, this->properties->Center.Y),
                        D2D1::Point2F(this->properties->GradientOriginOffset.X, this->properties->GradientOriginOffset.Y),
                        this->properties->RadiusX,
                        this->properties->RadiusY);
                    hr = renderTarget->CreateRadialGradientBrush(props, gradientStops, &brush);
                    if (SUCCEEDED(hr)) {
                        this->instance = brush;
                    }
                    else {
                        this->instance = NULL;
                    }
                    gradientStops->Release();
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
