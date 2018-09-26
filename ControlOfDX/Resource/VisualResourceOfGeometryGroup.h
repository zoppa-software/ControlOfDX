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
    using namespace System::Collections::Generic;

    /// <summary>ジオメトリグループリソース。</summary>
	public ref class VisualResourceOfGeometryGroup
		: public VisualResourceOfGeometry
	{
#pragma region "fields"
	private:
        // ジオメトリ
		ID2D1GeometryGroup * geometry;

#pragma endregion

#pragma region "constructor/destructor"
	public:
        /// <summary>コンストラクタ。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="fillMode">リソース名。</param>
        /// <param name="geometries">グループに含めるジオメトリリスト。</param>
        VisualResourceOfGeometryGroup(String ^ name,
                                      FillMode fillMode,
                                      IEnumerable<VisualResourceOfGeometry^>^ geometries)
			: VisualResourceOfGeometry(name)
		{
            if (!SingletonFactory::GetDirect2DFactory()) {
                throw gcnew ResourceException("ジオメトリグループの作成に失敗しました");
            }

            ID2D1GeometryGroup * geo;
            std::vector<ID2D1Geometry*> geos;
            for each (VisualResourceOfGeometry ^ item in geometries) {
                geos.push_back(item->GetGeometry());
            }

            HRESULT hr = SingletonFactory::GetDirect2DFactory()->CreateGeometryGroup((D2D1_FILL_MODE)fillMode, geos.data(), geos.size(), &geo);
			if (SUCCEEDED(hr)) {
				this->geometry = geo;
			}
			else {
                throw gcnew ResourceException("ジオメトリグループの作成に失敗しました");
			}
		}

        /// <summary>デストラクタ。</summary>
        virtual ~VisualResourceOfGeometryGroup()
        {
            if (this->geometry != NULL) {
                this->geometry->Release();
                this->geometry = NULL;
            }
        }

        /// <summary>ファイナライザ。</summary>
		!VisualResourceOfGeometryGroup()
        {
            this->~VisualResourceOfGeometryGroup();
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