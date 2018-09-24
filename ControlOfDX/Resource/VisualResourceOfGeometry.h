#pragma once

#include <vector>
#include "../ControlOfDX.h"
#include "VisualResource.h"

namespace ControlOfDX
{
    /// <summary>ジオメトリリソースインターフェース。</summary>
    public ref class VisualResourceOfGeometry abstract
        : VisualResource
	{
#pragma region "constructor/destructor"
    public:
        /// <summary>コンストラクタ。</summary>
        /// <param name="name">リソース名。</param>
        VisualResourceOfGeometry(String ^ name)
            : VisualResource(name)
        {}

        /// <summary>デストラクタ。</summary>
        virtual ~VisualResourceOfGeometry() {}

        /// <summary>ファイナライザ。</summary>
        !VisualResourceOfGeometry() {}

#pragma endregion

#pragma region "methods"
    internal:
        /// <summary>ジオメトリの実体を取得する。</summary>
        /// <return>ジオメトリ。</return>
        virtual ID2D1Geometry * GetGeometry() = 0;

#pragma endregion

	};
}
