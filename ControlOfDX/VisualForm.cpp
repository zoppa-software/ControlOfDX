#include "stdafx.h"
#include "VisualForm.h"
#include "SingletonFactory.h"

namespace ControlOfDX
{
    //---------------------------------------------------------------------
    // �R���X�g���N�^�A�f�X�g���N�^
    //---------------------------------------------------------------------
    VisualForm::VisualForm()
        : renderTarget(NULL)
    {
        ID2D1Factory * d2factory;
        IDWriteFactory * writeFactory;
        SingletonFactory::Regist(this, &d2factory, &writeFactory);
        this->factory = d2factory;
        this->writeFactory = writeFactory;

        this->resources = gcnew VisualResources();
    }

    VisualForm::~VisualForm()
    {
        this->ReleaseResources();
    }

    VisualForm::!VisualForm()
    {
        this->ReleaseResources();
    }

    void VisualForm::ReleaseResources()
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
    void VisualForm::WndProc(System::Windows::Forms::Message% m)
    {
        // �E�B���h�E�n���h�����擾
        HWND hWnd = (HWND)this->Handle.ToPointer();

        switch (m.Msg)
        {
        case WM_CREATE:
            this->OnInitializeResource(gcnew EventArgs());
            Form::WndProc(m);
            break;

        case WM_SIZE:
            // �T�C�Y�ύX
            {
                UINT width = LOWORD(m.LParam.ToPointer());
                UINT height = HIWORD(m.LParam.ToPointer());
                if (this->renderTarget != NULL) {
                    this->renderTarget->Resize(D2D1::SizeU(width, height));
                    ::InvalidateRect(hWnd, NULL, FALSE);
                }
            }
            break;

        case WM_DISPLAYCHANGE:
            // �f�B�X�v���C�`�F���W
            if (hWnd) {
                ::InvalidateRect(hWnd, NULL, FALSE);
            }
            else {
                Form::WndProc(m);
            }
            break;

        case WM_PAINT:
            // �`��C�x���g
            if (hWnd && !this->DesignMode) {
                this->RenderControl(hWnd);
                ::ValidateRect(hWnd, NULL);
            }
            else {
                Form::WndProc(m);
            }
            break;

        case WM_DESTROY:
            this->ReleaseResources();
            Form::WndProc(m);
            break;

        default:
            Form::WndProc(m);
            break;
        }
    }

    void VisualForm::OnPaintBackground(PaintEventArgs ^ e)
    {
        if (this->DesignMode) {
            Form::OnPaintBackground(e);
        }
    }

    void VisualForm::OnInitializeResource(EventArgs ^ e)
    {
        this->InitializeResource(this, e);
    }

    void VisualForm::OnRendering(VisualRenderEventArgs ^ e)
    {
        this->Rendering(this, e);
    }

    //---------------------------------------------------------------------
    // �`�揈��
    //---------------------------------------------------------------------
    void VisualForm::RenderControl(HWND hWnd)
    {
        HRESULT hr;

        // �`��^�[�Q�b�g���擾����
        hr = this->CreateDeviceResources();
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
    }

    HRESULT VisualForm::CreateDeviceResources()
    {
        HRESULT hr = S_OK;

        if (!this->renderTarget &&
            this->factory != NULL)
        {
            // �E�B���h�E�n���h�����擾
            HWND hWnd = (HWND)this->Handle.ToPointer();

            RECT rc;
            GetClientRect(hWnd, &rc);

            D2D1_SIZE_U size = D2D1::SizeU(
                rc.right - rc.left,
                rc.bottom - rc.top
            );

            ID2D1HwndRenderTarget * rend;
            hr = this->factory->CreateHwndRenderTarget(
                D2D1::RenderTargetProperties(),
                D2D1::HwndRenderTargetProperties(hWnd, size),
                &rend
            );
            if (SUCCEEDED(hr)) {
                this->renderTarget = rend;

                // ���\�[�X�����̂ɕϊ�
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

    void VisualForm::DiscardDeviceResources()
    {
        if (this->renderTarget) {
            this->renderTarget->Release();
            this->renderTarget = NULL;
        }

        for each(VisualResource ^ ins in this->resources->Values) {
            ins->ReleaseInstance();
        }
    }
}
