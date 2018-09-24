#pragma once

#include <vector>
#include "../ControlOfDX.h"
#include "../SingletonFactory.h"
#include "VisualResource.h"
#include "VisualResourceOfGeometry.h"

namespace ControlOfDX
{
    using namespace System;
    using namespace System::Drawing;

    /// <summary>パスジオメトリリソース。</summary>
	public ref class VisualResourceOfPathGeometry
		: public VisualResourceOfGeometry
	{
#pragma region "fields"
	private:
        // パスジオメトリ
		ID2D1PathGeometry * geometry;

#pragma endregion

#pragma region "constructor/destructor"
	public:
        /// <summary>コンストラクタ。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="factory">レンダーファクトリ。</param>
		VisualResourceOfPathGeometry(String ^ name)
			: VisualResourceOfGeometry(name)
		{
            if (!SingletonFactory::GetDirect2DFactory()) {
                throw gcnew ResourceException("パスジオメトリの作成に失敗しました");
            }

			ID2D1PathGeometry * geo;
			HRESULT hr = SingletonFactory::GetDirect2DFactory()->CreatePathGeometry(&geo);
			if (SUCCEEDED(hr)) {
				this->geometry = geo;
			}
			else {
				throw gcnew ResourceException("パスジオメトリの作成に失敗しました");
			}
		}

        /// <summary>デストラクタ。</summary>
        virtual ~VisualResourceOfPathGeometry()
        {
            if (this->geometry != NULL) {
                this->geometry->Release();
                this->geometry = NULL;
            }
        }

        /// <summary>ファイナライザ。</summary>
        !VisualResourceOfPathGeometry()
        {
            this->~VisualResourceOfPathGeometry();
        }

#pragma endregion

#pragma region "methods"
	public:
        /// <summary>ジオメトリシンクを作成する。</summary>
        /// <return>ジオメトリシンク。</return>
		GeometrySink ^ CreateGeometrySink()
		{
			ID2D1GeometrySink * sink;
			HRESULT hr = this->geometry->Open(&sink);
			if (SUCCEEDED(hr)) {
				return gcnew GeometrySink(sink);
			}
			else {
				throw gcnew ResourceException("ジオメトリシンクの作成に失敗しました");
			}
		}

    internal:
        /// <summary>リソースを使用する準備を行う。</summary>
        /// <param name="name">レンダーターゲット。</param>
        void Preparation(ID2D1RenderTarget * renderTarget) override
        {

        }

        /// <summary>パスジオメトリの実体を取得する。</summary>
        /// <return>パスジオメトリ。</return>
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
