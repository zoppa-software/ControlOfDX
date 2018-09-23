#include "stdafx.h"
#include "VisualControl.h"
#include "SingletonFactory.h"

namespace ControlOfDX
{
    //---------------------------------------------------------------------
    // コンストラクタ、デストラクタ
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
            // レンダーターゲットを解放
            this->renderTarget->Release();
            this->renderTarget = NULL;

            // リソースを解放
            for each(VisualResource ^ ins in this->resources->Values) {
                delete ins;
            }

            // 参照しているフォームが無くなったなら解放
            SingletonFactory::Unregist(this);
        }
    }

    //---------------------------------------------------------------------
    // イベント処理
    //---------------------------------------------------------------------
    void VisualControl::WndProc(System::Windows::Forms::Message% m)
    {
        // ウィンドウハンドルを取得
        HWND hWnd = (HWND)this->Handle.ToPointer();

        switch (m.Msg)
        {
        case WM_CREATE:
            this->OnInitializeResource(gcnew EventArgs());
            Control::WndProc(m);
            break;

        case WM_SIZE:
            // ディスプレイチェンジ
            if (hWnd) {
                ::InvalidateRect(hWnd, NULL, FALSE);
            }
            else {
                Control::WndProc(m);
            }
            break;

        case WM_PAINT:
        case WM_DISPLAYCHANGE:
            // 描画イベント
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
    // 描画処理
    //---------------------------------------------------------------------
    void VisualControl::RenderControl(HWND hWnd)
    {
        HRESULT hr;
        RECT rc;

        // 描画開始
        PAINTSTRUCT ps;
        ::BeginPaint(hWnd, &ps);

        // 描画範囲を取得する
        ::GetClientRect(hWnd, &rc);

        // 描画ターゲットを取得する
        hr = this->CreateDeviceResources();
        if (FAILED(hr) || this->renderTarget == NULL) {
            goto LAST;
        }

        // デバイスコンテキストにレンダーターゲットを紐付ける
        hr = this->renderTarget->BindDC(ps.hdc, &rc);
        if (FAILED(hr) || this->renderTarget == NULL) {
            goto LAST;
        }

        // Direct2D描画開始
        this->renderTarget->BeginDraw();

        // Direct2D描画
        try {
            VisualRenderTarget ^ render = gcnew VisualRenderTarget(this->renderTarget);
            this->renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
            this->OnRendering(gcnew VisualRenderEventArgs(render, this->resources));
        }
        catch (NullReferenceException ^) {
            // 空ポインタ参照を無視
        }

        // Direct2D描画終了
        hr = this->renderTarget->EndDraw();
    LAST:
        // デバイスロスト対応
        if (hr == D2DERR_RECREATE_TARGET) {
            this->DiscardDeviceResources();
        }

        // 描画終了
        ::EndPaint(hWnd, &ps);
    }

    HRESULT VisualControl::CreateDeviceResources()
    {
        HRESULT hr = S_OK;

        if (!this->renderTarget &&
            this->factory != NULL)
        {
            // ウィンドウハンドルを取得
            HWND hWnd = (HWND)this->Handle.ToPointer();

            // プロパティ設定
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

            // レンダーターゲットを生成
            ID2D1DCRenderTarget * rend;
            hr = factory->CreateDCRenderTarget(&props, &rend);   
            if (SUCCEEDED(hr)) {
                this->renderTarget = rend;

                // リソースを実体に変換
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
