#pragma once

namespace ControlOfDX
{
    using namespace System::Drawing;

    /// <summary>楕円の中心点、X半径、および Y半径を格納します。</summary>
    public value class Ellipse
    {
    private:
        // 楕円の中心点
        PointF  point;

        // 楕円のX半径
        float   radiusX;

        // 楕円のY半径
        float   radiusY;

    public:
        /// <summary>楕円の中心点を設定、取得する。</summary>
        property PointF CenterPoint {
            PointF get() { return this->point; }
            void set(PointF value) { this->point = value; }
        }

        /// <summary>楕円のX半径を設定、取得する。</summary>
        property float RadiusX {
            float get() { return this->radiusX; }
            void set(float value) { this->radiusX = value; }
        }

        /// <summary>楕円のY半径を設定、取得する。</summary>
        property float RadiusY {
            float get() { return this->radiusY; }
            void set(float value) { this->radiusY = value; }
        }

    public:
        /// <summary>コンストラクタ。</summary>
        /// <param name="point">楕円の中心点。</param>
        /// <param name="radiusX">楕円のX半径。</param>
        /// <param name="radiusY">楕円のY半径。</param>
        Ellipse(PointF point, float radiusX, float radiusY)
            : point(point), radiusX(radiusX), radiusY(radiusY)
        {}
    };
}

