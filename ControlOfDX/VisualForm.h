#pragma once

#include "ControlOfDX.h"
#include "VisualRenderEventArgs.h"
#include "Resource\VisualResources.h"

namespace ControlOfDX
{
    using namespace System;
    using namespace System::Windows::Forms;;
    using namespace System::ComponentModel;

    /// <summary>DirectXで描画を行うウィンドウ。</summary>
    public ref class VisualForm
        : System::Windows::Forms::Form
    {
    public:
        /// <summary>描画処理イベントデリゲート。</summary>
        /// <param name="sender">イベント発行元。</param>
        /// <param name="e">イベントオブジェクト。</param>
        delegate void VisualRenderEventHandler(Object ^ sender, VisualRenderEventArgs ^ e);

        /// <summary>リソースの初期化を行う。</summary>
        [Category("DirectX")]
        [Description("リソースの初期化を行う")]
        event EventHandler ^ InitializeResource;

        /// <summary>描画を行う。</summary>
        [Category("DirectX")]
        [Description("描画を行う")]
        event VisualRenderEventHandler ^ Rendering;

#pragma region "properties"
    public:
        /// <summary>リソースを取得する。</summary>
        property VisualResources ^ Resources {
            VisualResources ^ get() { return this->resources; }
        }

#pragma endregion

#pragma region "fields"
    private:
        // ファクトリ
        ID2D1Factory * factory;

        // DirectWriteファクトリ
        IDWriteFactory * writeFactory;

        // リソースリスト
        VisualResources ^ resources;

        // レンダーターゲット
        ID2D1HwndRenderTarget * renderTarget;

#pragma endregion

#pragma region "constructor/destructor"
    public:
        /// <summary>コンストラクタ。</summary>
        VisualForm();

        /// <summary>デストラクタ。</summary>
        virtual ~VisualForm();

        /// <summary>ファイナライザ。</summary>
        !VisualForm();

#pragma endregion

#pragma region "methods"
    private:
        /// <summary>リソースの解放を行う。</summary>
        void ReleaseResources();

        //---------------------------------------------------------------------
        // イベント処理
        //---------------------------------------------------------------------
    protected:
        /// <summary>ウィンドウプロシージャ。</summary>
        /// <param name="m">メッセージ構造体。</param>
        virtual void WndProc(System::Windows::Forms::Message% m) override;

        /// <summary>背景描画イベント。</summary>
        /// <param name="e">イベントオブジェクト。</param>
        void OnPaintBackground(PaintEventArgs ^ e) override;

        /// <summary>リソース初期化を行う。</summary>
        /// <param name="e">イベントオブジェクト。</param>
        virtual void OnInitializeResource(EventArgs ^ e);

        /// <summary>描画処理を行う。</summary>
        /// <param name="e">イベントオブジェクト。</param>
        virtual void OnRendering(VisualRenderEventArgs ^ e);

        //---------------------------------------------------------------------
        // 描画処理
        //---------------------------------------------------------------------
    private:
        /// <summary>描画を行う。</summary>
        /// <param name="hWnd">ウィンドウハンドル。</param>
        void RenderControl(HWND hWnd);

        /// <summary>デバイス依存リソースを作成する。</summary>
        /// <return>実行結果。</return>
        HRESULT CreateDeviceResources();

        /// <summary>デバイスロスト向け、リソース解放処理。</summary>
        void DiscardDeviceResources();

#pragma endregion
    };
}
