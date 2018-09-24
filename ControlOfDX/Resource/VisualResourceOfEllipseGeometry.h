#pragma once

#include "../ControlOfDX.h"
#include "../SingletonFactory.h"
#include "VisualResource.h"
#include "VisualResourceOfGeometry.h"
#include "VisualResourceOfPathGeometry.h"

namespace ControlOfDX
{
    using namespace System;
    using namespace System::Drawing;

    /// <summary>�~�`�W�I���g�����\�[�X�B</summary>
    public ref class VisualResourceOfEllipseGeometry
        : public VisualResourceOfGeometry
    {
#pragma region "fields"
    private:
        // �W�I���g��
        ID2D1EllipseGeometry * geometry;

#pragma endregion

#pragma region "constructor/destructor"
    public:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="ellipse">�Ώۉ~�`�B</param>
        VisualResourceOfEllipseGeometry(String ^ name,
                                        Ellipse ellipse)
            : VisualResourceOfGeometry(name)
        {
            if (!SingletonFactory::GetDirect2DFactory()) {
                throw gcnew ResourceException("�~�`�W�I���g���̍쐬�Ɏ��s���܂���");
            }

            D2D1_ELLIPSE ell = D2D1::Ellipse(D2D1::Point2F(ellipse.CenterPoint.X, ellipse.CenterPoint.Y),
                                             ellipse.RadiusX,
                                             ellipse.RadiusY);
             
            ID2D1EllipseGeometry * geo;
            HRESULT hr = SingletonFactory::GetDirect2DFactory()->CreateEllipseGeometry(ell, &geo);
            if (SUCCEEDED(hr)) {
                this->geometry = geo;
            }
            else {
                throw gcnew ResourceException("�~�`�W�I���g���̍쐬�Ɏ��s���܂���");
            }
        }

        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="centerPoint">�ȉ~�̒��S�B</param>
        /// <param name="radiusX">�ȉ~��X���a�B</param>
        /// <param name="radiusY">�ȉ~��Y���a�B</param>
        VisualResourceOfEllipseGeometry(String ^ name,
                                        PointF centerPoint,
                                        float radiusX,
                                        float radiusY)
            : VisualResourceOfGeometry(name)
        {
            if (!SingletonFactory::GetDirect2DFactory()) {
                throw gcnew ResourceException("�~�`�W�I���g���̍쐬�Ɏ��s���܂���");
            }

            D2D1_ELLIPSE ell = D2D1::Ellipse(D2D1::Point2F(centerPoint.X, centerPoint.Y), radiusX, radiusY);

            ID2D1EllipseGeometry * geo;
            HRESULT hr = SingletonFactory::GetDirect2DFactory()->CreateEllipseGeometry(ell, &geo);
            if (SUCCEEDED(hr)) {
                this->geometry = geo;
            }
            else {
                throw gcnew ResourceException("�~�`�W�I���g���̍쐬�Ɏ��s���܂���");
            }
        }

        /// <summary>�f�X�g���N�^�B</summary>
        virtual ~VisualResourceOfEllipseGeometry()
        {
            if (this->geometry != NULL) {
                this->geometry->Release();
                this->geometry = NULL;
            }
        }

        /// <summary>�t�@�C�i���C�U�B</summary>
        !VisualResourceOfEllipseGeometry()
        {
            this->~VisualResourceOfEllipseGeometry();
        }

#pragma endregion

#pragma region "methods"
    internal:
        /// <summary>���\�[�X���g�p���鏀�����s���B</summary>
        /// <param name="name">�����_�[�^�[�Q�b�g�B</param>
        void Preparation(ID2D1RenderTarget * renderTarget) override
        {

        }

        /// <summary>�~�`�W�I���g���̎��̂��擾����B</summary>
        /// <return>�~�`�W�I���g���B</return>
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