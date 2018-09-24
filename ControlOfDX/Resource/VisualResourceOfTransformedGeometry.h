#pragma once

#include "../ControlOfDX.h"
#include "../SingletonFactory.h"
#include "VisualResource.h"
#include "VisualResourceOfGeometry.h"
#include "VisualResourceOfPathGeometry.h"
#include "VisualResourceOfRectangleGeometry.h"

namespace ControlOfDX
{
    using namespace System;
    using namespace System::Drawing;

    /// <summary>変形ジオメトリリソース。</summary>
	public ref class VisualResourceOfTransformedGeometry
		: public VisualResourceOfGeometry
	{
#pragma region "fields"
	private:
        // ジオメトリ
		ID2D1TransformedGeometry * geometry;

#pragma endregion

#pragma region "constructor/destructor"
	public:
        /// <summary>コンストラクタ。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="geometry">ジオメトリ。</param>
        /// <param name="matrix">変形量。</param>
		VisualResourceOfTransformedGeometry(String ^ name,
                                            VisualResourceOfGeometry ^ geometry,
                                            Matrix matrix)
			: VisualResourceOfGeometry(name)
		{
            if (!SingletonFactory::GetDirect2DFactory()) {
                throw gcnew ResourceException("変形ジオメトリの作成に失敗しました");
            }

			ID2D1TransformedGeometry * geo;
			HRESULT hr = SingletonFactory::GetDirect2DFactory()->CreateTransformedGeometry(geometry->GetGeometry(), matrix.Convert(), &geo);
			if (SUCCEEDED(hr)) {
				this->geometry = geo;
			}
			else {
                throw gcnew ResourceException("変形ジオメトリの作成に失敗しました");
			}
		}

        /// <summary>デストラクタ。</summary>
        virtual ~VisualResourceOfTransformedGeometry()
        {
            if (this->geometry != NULL) {
                this->geometry->Release();
                this->geometry = NULL;
            }
        }

        /// <summary>ファイナライザ。</summary>
        !VisualResourceOfTransformedGeometry()
        {
            this->~VisualResourceOfTransformedGeometry();
        }

#pragma endregion

#pragma region "methods"
    internal:
        /// <summary>リソースを使用する準備を行う。</summary>
        /// <param name="name">レンダーターゲット。</param>
        void Preparation(ID2D1RenderTarget * renderTarget) override
        {

        }

        /// <summary>変形ジオメトリの実体を取得する。</summary>
        /// <return>変形ジオメトリ。</return>
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