#pragma once

#include "../ControlOfDX.h"
#include "../SingletonFactory.h"
#include "VisualResource.h"
#include "VisualResourceOfGeometry.h"

namespace ControlOfDX
{
    using namespace System;
    using namespace System::Drawing;

    /// <summary>矩形ジオメトリリソース。</summary>
	public ref class VisualResourceOfRectangleGeometry
		: public VisualResourceOfGeometry
	{
#pragma region "fields"
	private:
        // ジオメトリ
		ID2D1RectangleGeometry * geometry;

#pragma endregion

#pragma region "constructor/destructor"
	public:
        /// <summary>コンストラクタ。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="rectangle">対象矩形。</param>
		VisualResourceOfRectangleGeometry(String ^ name,
                                          RectangleF rectangle)
			: VisualResourceOfGeometry(name)
		{
            if (!SingletonFactory::GetDirect2DFactory()) {
                throw gcnew ResourceException("矩形ジオメトリの作成に失敗しました");
            }

            D2D1_RECT_F rec = D2D1::RectF(rectangle.Left,
                                          rectangle.Top,
                                          rectangle.Right,
                                          rectangle.Bottom);
			ID2D1RectangleGeometry * geo;
			HRESULT hr = SingletonFactory::GetDirect2DFactory()->CreateRectangleGeometry(rec, &geo);
			if (SUCCEEDED(hr)) {
				this->geometry = geo;
			}
			else {
                throw gcnew ResourceException("矩形ジオメトリの作成に失敗しました");
			}
		}

        /// <summary>デストラクタ。</summary>
        virtual ~VisualResourceOfRectangleGeometry()
        {
            if (this->geometry != NULL) {
                this->geometry->Release();
                this->geometry = NULL;
            }
        }

        /// <summary>ファイナライザ。</summary>
		!VisualResourceOfRectangleGeometry()
        {
            this->~VisualResourceOfRectangleGeometry();
        }

#pragma endregion

#pragma region "methods"
    internal:
        /// <summary>リソースを使用する準備を行う。</summary>
        /// <param name="name">レンダーターゲット。</param>
        void Preparation(ID2D1RenderTarget * renderTarget) override
        {

        }

        /// <summary>矩形ジオメトリの実体を取得する。</summary>
        /// <return>矩形ジオメトリ。</return>
        ID2D1Geometry * GetGeometry() override {
            return this->geometry;
        }

        /// <summary>Direct2Dのインスタンスを取得する。</summary>
        ID2D1Resource * GetInstance() override
        {
            return this->geometry;
        }

#pragma endregion
	};
}