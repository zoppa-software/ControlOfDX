#pragma once

#include "VisualRenderTarget.h"
#include "Resource\VisualResources.h"

namespace ControlOfDX
{
    using namespace System;

    /// <summary>描画イベントオブジェクト。</summary>
    public ref class VisualRenderEventArgs sealed
        : EventArgs
    {
    private:
        // 描画対象
        VisualRenderTarget ^ render;

        // リソースコレクション
        VisualResources ^ resources;

    public:
        /// <summary>描画対象インスタンスを取得する。</summary>
        property VisualRenderTarget ^ RenderTarget {
            VisualRenderTarget ^ get() { return this->render; }
        }

        /// <summary>リソースコレクションを取得する。</summary>
        property VisualResources ^ Resources {
            VisualResources ^ get() { return this->resources; }
        }

    public:
        /// <summary>コンストラクタ。</summary>
        /// <param name="renderTarget">レンダリングターゲット。</param>
        /// <param name="resources">リソースコレクション。</param>
        VisualRenderEventArgs(VisualRenderTarget ^ renderTarget, VisualResources ^ resources)
            : render(renderTarget), resources(resources)
        {}
    };
}
