#pragma once

#include <limits>
#include "ControlOfDX.h"
#include "Resource\VisualResource.h"

namespace ControlOfDX
{
    using namespace System;
    using namespace System::Drawing;

    /// <summary>描画レイヤー。</summary>
    public ref class Layer sealed
        : IDisposable
    {
    public:
        /// <summary>レイヤー リソースのコンテンツの境界、マスク情報、不透明度の設定、およびその他のオプションを格納します。</summary>
        ref class LayerParameters
        {
        private:
            // レイヤーのコンテンツの境界
            RectangleF contentBounds;

            // ジオメトリマスクは、レンダー ターゲットに統合されているレイヤーの領域を指定します
            VisualResource ^ geometricMask;

            // アンチエイリアシングモードを指定する値
            AntialiasMode maskAntialiasMode;

            // レイヤーの作成時にジオメトリマスクに適用される変換を指定する値
            Matrix maskTransform;

            // ターゲットに統合されるときにレイヤー内のすべてのリソースに一律に適用される不透明度の値
            float opacity;

            // レイヤーの不透明度の変更に使用されるブラシ
            VisualResource ^ opacityBrush;

            // レイヤーが ClearType アンチエイリアシングを使用してテキストをレンダリングするかどうかを指定する値
            LayerOptions layerOptions;

        public:
            /// <summary>レイヤーのコンテンツの境界を設定、取得する。</summary>
            property RectangleF ContentBounds {
                RectangleF get() { return this->contentBounds; }
                void set(RectangleF value) { this->contentBounds = value; }
            }

            /// <summary>ジオメトリマスクを設定、取得する。</summary>
            property VisualResource ^ GeometricMask {
                VisualResource ^ get() { return this->geometricMask; }
                void set(VisualResource ^ value) { this->geometricMask = value; }
            }

            /// <summary>アンチエイリアシングモードを設定、取得する。</summary>
            property AntialiasMode MaskAntialiasMode {
                AntialiasMode get() { return this->maskAntialiasMode; }
                void set(AntialiasMode value) { this->maskAntialiasMode = value; }
            }

            /// <summary>レイヤーの作成時にジオメトリマスクを設定、取得する。</summary>
            property Matrix MaskTransform {
                Matrix get() { return this->maskTransform; }
                void set(Matrix value) { this->maskTransform = value; }
            }

            /// <summary>レイヤーが ClearType アンチエイリアシングを使用してテキストをレンダリングするかどうかを指定する値を設定、取得する。</summary>
            property float Opacity {
                float get() { return this->opacity; }
                void set(float value) { this->opacity = value; }
            }

            /// <summary>レイヤーの不透明度の変更に使用されるブラシを設定、取得する。</summary>
            property VisualResource ^ OpacityBrush {
                VisualResource ^ get() { return this->opacityBrush; }
                void set(VisualResource ^ value) { this->opacityBrush = value; }
            }

            /// <summary>不透明度の値を設定、取得する。</summary>
            property ControlOfDX::LayerOptions LayerOptions {
                ControlOfDX::LayerOptions get() { return this->layerOptions; }
                void set(ControlOfDX::LayerOptions value) { this->layerOptions = value; }
            }

        public:
            /// <summary>コンストラクタ。</summary>
            LayerParameters()
                : contentBounds(RectangleF(FLT_MIN, FLT_MIN, FLT_MAX, FLT_MAX)),
                geometricMask(nullptr),
                maskAntialiasMode(AntialiasMode::ANTIALIAS_MODE_PER_PRIMITIVE),
                maskTransform(Matrix::Identity()),
                opacity(1),
                opacityBrush(nullptr),
                layerOptions(ControlOfDX::LayerOptions::D2D1_LAYER_OPTIONS_NONE)
            {}
        };

    private:
        // レイヤー参照
        ID2D1Layer * layer;

        // レイヤーパラメータ
        LayerParameters ^ parameters;

    public:
        /// <summary>レイヤーパラメータを取得する。</summary>
        property LayerParameters ^ Parameters
        {
            LayerParameters ^ get() {
                return this->parameters;
            }
        }

    internal:
        /// <summary>コンストラクタ。</summary>
        Layer()
            : layer(NULL)
        {
            this->parameters = gcnew LayerParameters();
        }

        /// <summary>コンストラクタ。</summary>
        /// <param name="layer">対象レイヤー。</param>
        Layer(ID2D1Layer * layer)
            : layer(layer)
        {
            this->parameters = gcnew LayerParameters();
        }

    public:
        /// <summary>デストラクタ。</summary>
        ~Layer()
        {
            if (this->layer != NULL) {
                this->layer->Release();
                this->layer = NULL;
            }
        }

        /// <summary>ファイナライザ。</summary>
        !Layer()
        {
            this->~Layer();
        }

    internal:
        /// <summary>対象レイヤーのポインタを取得する。</summary>
        /// <return>対象レイヤー。</return>
        ID2D1Layer * GetInstance() { return this->layer; }
    };
}
