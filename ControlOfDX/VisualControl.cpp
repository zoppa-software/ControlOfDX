#include "stdafx.h"
#include "VisualControl.h"
#include "SingletonFactory.h"

namespace ControlOfDX
{
    //---------------------------------------------------------------------
    // �R���X�g���N�^�A�f�X�g���N�^
    //---------------------------------------------------------------------
    VisualControl::VisualControl()
        : renderTarget(NULL)
    {
        ID2D1Factory * d2factory;
        IDWriteFactory * writeFactory;
        SingletonFactory::Regist(this, &d2factory, &writeFactory);
        this->factory = d2factory;
        this->writeFactory = writeFactory;

        this->resources = gcnew VisualResources();
    }

    VisualControl::~VisualControl()
    {
        this->ReleaseResources();
    }

    VisualControl::!VisualControl()
    {
        this->ReleaseResources();
    }

    void VisualControl::ReleaseResources()
    {
        if (this->renderTarget) {
            // �����_�[�^�[�Q�b�g�����
            this->renderTarget->Release();
            this->renderTarget = NULL;

            // ���\�[�X�����
            for each(VisualResource ^ ins in this->resources->Values) {
                delete ins;
            }

            // �Q�Ƃ��Ă���t�H�[���������Ȃ����Ȃ���
            SingletonFactory::Unregist(this);
        }
    }

    //---------------------------------------------------------------------
    // �C�x���g����
    //---------------------------------------------------------------------
    void VisualControl::WndProc(System::Windows::Forms::Message% m)
    {
        // �E�B���h�E�n���h�����擾
        HWND hWnd = (HWND)this->Handle.ToPointer();

        switch (m.Msg)
        {
        case WM_CREATE:
            this->OnInitializeResource(gcnew EventArgs());
            Control::WndProc(m);
            break;

        case WM_SIZE:
            // �f�B�X�v���C�`�F���W
            if (hWnd) {
                ::InvalidateRect(hWnd, NULL, FALSE);
            }
            else {
                Control::WndProc(m);
            }
            break;

        case WM_PAINT:
        case WM_DISPLAYCHANGE:
            // �`��C�x���g
            if (hWnd && !this->DesignMode) {
                this->RenderControl(hWnd);
            }
            else {
                Control::WndProc(m);
            }
            break;

        default:
            Control::WndProc(m);
            break;
        }
    }

    void VisualControl::OnPaintBackground(PaintEventArgs ^ e)
    {
        if (this->DesignMode) {
            Control::OnPaintBackground(e);
        }
    }

    void VisualControl::OnInitializeResource(EventArgs ^ e)
    {
        this->InitializeResource(this, e);
    }

    void VisualControl::OnRendering(VisualRenderEventArgs ^ e)
    {
        this->Rendering(this, e);
    }

    //---------------------------------------------------------------------
    // �`�揈��
    //---------------------------------------------------------------------
    void VisualControl::RenderControl(HWND hWnd)
    {
        HRESULT hr;
        RECT rc;

        // �`��J�n
        PAINTSTRUCT ps;
        ::BeginPaint(hWnd, &ps);

        // �`��͈͂��擾����
        ::GetClientRect(hWnd, &rc);

        // �`��^�[�Q�b�g���擾����
        hr = this->CreateDeviceResources();
        if (FAILED(hr) || this->renderTarget == NULL) {
            goto LAST;
        }

        // �f�o�C�X�R���e�L�X�g�Ƀ����_�[�^�[�Q�b�g��R�t����
        hr = this->renderTarget->BindDC(ps.hdc, &rc);
        if (FAILED(hr) || this->renderTarget == NULL) {
            goto LAST;
        }

        // Direct2D�`��J�n
        this->renderTarget->BeginDraw();

        // Direct2D�`��
        try {
            VisualRenderTarget ^ render = gcnew VisualRenderTarget(this->renderTarget);
            this->renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
            this->OnRendering(gcnew VisualRenderEventArgs(render, this->resources));
        }
        catch (NullReferenceException ^) {
            // ��|�C���^�Q�Ƃ𖳎�
        }

        // Direct2D�`��I��
        hr = this->renderTarget->EndDraw();
    LAST:
        // �f�o�C�X���X�g�Ή�
        if (hr == D2DERR_RECREATE_TARGET) {
            this->DiscardDeviceResources();
        }

        // �`��I��
        ::EndPaint(hWnd, &ps);
    }

    HRESULT VisualControl::CreateDeviceResources()
    {
        HRESULT hr = S_OK;

        if (!this->renderTarget &&
            this->factory != NULL)
        {
            // �E�B���h�E�n���h�����擾
            HWND hWnd = (HWND)this->Handle.ToPointer();

            // �v���p�e�B�ݒ�
            D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
                D2D1_RENDER_TARGET_TYPE_DEFAULT,
                D2D1::PixelFormat(
                    DXGI_FORMAT_B8G8R8A8_UNORM,
                    D2D1_ALPHA_MODE_IGNORE),
                0,
                0,
                D2D1_RENDER_TARGET_USAGE_NONE,
                D2D1_FEATURE_LEVEL_DEFAULT
            );

            // �����_�[�^�[�Q�b�g�𐶐�
            ID2D1DCRenderTarget * rend;
            hr = factory->CreateDCRenderTarget(&props, &rend);   
            if (SUCCEEDED(hr)) {
                this->renderTarget = rend;

                // ���\�[�X�����̂ɕϊ�
                for each (VisualResource ^ res in this->resources->Values) {
                    res->PreparationImage(this->renderTarget);
                }
                for each (VisualResource ^ res in this->resources->Values) {
                    res->Preparation(this->renderTarget);
                }
            }
            else {
                this->renderTarget = NULL;
            }
        }

        return hr;
    }

    void VisualControl::DiscardDeviceResources()
    {
        if (this->renderTarget) {
            this->renderTarget->Release();
            this->renderTarget = NULL;
        }

        for each(VisualResource ^ ins in this->resources->Values) {
            ins->ReleaseInstance();
        }
    }

    void VisualControl::RebuildRenderer()
    {
        if (this->renderTarget != NULL) {
            this->renderTarget->Release();
            this->renderTarget = NULL;
            this->Invalidate();
        }
    }
}
