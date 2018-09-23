#pragma once

#include "../ControlOfDX.h"
#include "VisualResource.h"

namespace ControlOfDX
{
    using namespace System;
    using namespace System::Drawing;
    using namespace System::Drawing::Imaging;

    /// <summary>ビットマップリソース。</summary>
    public ref class VisualResourceOfBitmap sealed
        : public VisualResource
    {
#pragma region "fields"
    private:
        // 描画ビットマップ
        Bitmap ^    bitmap;

        // Direct2Dビットマップ
        ID2D1Bitmap * d2bitmap;

#pragma endregion

#pragma region "properties"
    public:
        /// <summary>描画するビットマップを設定、取得する。</summary>
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
        /// <summary>コンストラクタ。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="bitmap">描画ビットマップ。</param>
		VisualResourceOfBitmap(String ^ name, Bitmap ^ bitmap)
			: VisualResource(name), d2bitmap(NULL)
		{
            this->Source = bitmap;
        }

        /// <summary>デストラクタ。</summary>
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

        /// <summary>ファイナライザ。</summary>
        !VisualResourceOfBitmap()
        {
            this->~VisualResourceOfBitmap();
        }

#pragma endregion

#pragma region "methods"
    internal:
        /// <summary>リソースを使用する準備を行う。</summary>
        /// <param name="name">レンダーターゲット。</param>
        void Preparation(ID2D1RenderTarget * renderTarget) override
        {
            if (this->d2bitmap == NULL) {
                // ビットマップ描画ターゲットの作成
                ID2D1BitmapRenderTarget * bitmapTarget = NULL;
                HRESULT hr = renderTarget->CreateCompatibleRenderTarget(
                    D2D1::SizeF((float)this->bitmap->Width, (float)this->bitmap->Height),
                    &bitmapTarget
                );

                ID2D1Bitmap * bitmap = NULL;
                if (SUCCEEDED(hr)) {
                    // 描画するビットマップを取得       
                    hr = bitmapTarget->GetBitmap(&bitmap);

                    if (SUCCEEDED(hr)) {
                        // 描画ビットマップからビットマップ情報を取得し、コピーする
                        BitmapData ^ bmpData = this->bitmap->LockBits(System::Drawing::Rectangle(0, 0, this->bitmap->Width, this->bitmap->Height),
                                                                      ImageLockMode::ReadWrite,
                                                                      PixelFormat::Format32bppArgb);
                        D2D1_RECT_U rec = D2D1::RectU(0, 0, this->bitmap->Width, this->bitmap->Height);
                        bitmap->CopyFromMemory(&rec, (void*)bmpData->Scan0, bmpData->Stride);
                        this->bitmap->UnlockBits(bmpData);
                    }

                    // ビットマップ描画ターゲットの解放
                    bitmapTarget->Release();
                    this->d2bitmap = bitmap;
                }
            }
        }

    internal:
        /// <summary>Direct2Dのインスタンスを取得する。</summary>
        ID2D1Resource * GetInstance() override
        {
            return this->d2bitmap;
        }

#pragma endregion
    };
}