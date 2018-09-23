#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

namespace ControlOfDX
{
    /// <summary>座標変換マトリクス。</summary>
    public value class Matrix
    {
    private:
        // 変換値
        float _11, _12;
        float _21, _22;
        float _31, _32;

    public:
        /// <summary>無変換のマトリクスを取得する。</summary>
        /// <return>マトリクス。</return>
        static Matrix Identity()
        {
            Matrix res;
            res._11 = 1.f;
            res._12 = 0.f;
            res._21 = 0.f;
            res._22 = 1.f;
            res._31 = 0.f;
            res._32 = 0.f;
            return res;
        }

        /// <summary>マトリクスをDirect2D用のマトリクスに変換する。</summary>
        /// <return>マトリクス。</return>
        D2D1_MATRIX_3X2_F Convert()
        {
            return D2D1::Matrix3x2F(
                this->_11,
                this->_12,
                this->_21,
                this->_22,
                this->_31,
                this->_32
            );
        }

        /// <summary>移動マトリクスを取得する。</summary>
        /// <param name="size">移動量。</param>
        /// <return>マトリクス。</return>
        static Matrix Translation(System::Drawing::SizeF size)
        {
            Matrix res;
            res._11 = 1.f;
            res._12 = 0.f;
            res._21 = 0.f;
            res._22 = 1.f;
            res._31 = size.Width;
            res._32 = size.Height;
            return res;
        }

        /// <summary>移動マトリクスを取得する。</summary>
        /// <param name="x">X移動量。</param>
        /// <param name="y">Y移動量。</param>
        /// <return>マトリクス。</return>
        static Matrix Translation(float x, float y)
        {
            Matrix res;
            res._11 = 1.f;
            res._12 = 0.f;
            res._21 = 0.f;
            res._22 = 1.f;
            res._31 = x;
            res._32 = y;
            return res;
        }

        /// <summary>回転マトリクスを取得する。</summary>
        /// <param name="angle">回転角度。</param>
        /// <param name="center">中心位置。</param>
        /// <return>マトリクス。</return>
        static Matrix Rotation(float angle, System::Drawing::PointF center)
        {
            Matrix res;
            D2D1::Matrix3x2F max = D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(center.X, center.Y));

            res._11 = max._11;
            res._12 = max._12;
            res._21 = max._21;
            res._22 = max._22;
            res._31 = max._31;
            res._32 = max._32;
            return res;
        }

        /// <summary>回転マトリクスを取得する。</summary>
        /// <param name="angle">回転角度。</param>
        /// <return>マトリクス。</return>
        static Matrix Rotation(float angle)
        {
            Matrix res;
            D2D1::Matrix3x2F max = D2D1::Matrix3x2F::Rotation(angle);
            res._11 = max._11;
            res._12 = max._12;
            res._21 = max._21;
            res._22 = max._22;
            res._31 = max._31;
            res._32 = max._32;
            return res;
        }

        /// <summary>拡大・縮小マトリクスを取得する。</summary>
        /// <param name="x">x拡大量。</param>
        /// <param name="y">y拡大量。</param>
        /// <param name="center">中心位置。</param>
        /// <return>マトリクス。</return>
        static Matrix Scale(float x, float y, System::Drawing::PointF center)
        {
            Matrix res;
            D2D1::Matrix3x2F max = D2D1::Matrix3x2F::Scale(x, y, D2D1::Point2F(center.X, center.Y));
            res._11 = max._11;
            res._12 = max._12;
            res._21 = max._21;
            res._22 = max._22;
            res._31 = max._31;
            res._32 = max._32;
            return res;
        }

        /// <summary>拡大・縮小マトリクスを取得する。</summary>
        /// <param name="x">x拡大量。</param>
        /// <param name="y">y拡大量。</param>
        /// <return>マトリクス。</return>
        static Matrix Scale(float x, float y)
        {
            Matrix res;
            D2D1::Matrix3x2F max = D2D1::Matrix3x2F::Scale(x, y);
            res._11 = max._11;
            res._12 = max._12;
            res._21 = max._21;
            res._22 = max._22;
            res._31 = max._31;
            res._32 = max._32;
            return res;
        }

        /// <summary>拡大・縮小マトリクスを取得する。</summary>
        /// <param name="size">拡大量。</param>
        /// <param name="center">中心位置。</param>
        /// <return>マトリクス。</return>
        static Matrix Scale(System::Drawing::SizeF size, System::Drawing::PointF center)
        {
            Matrix res;
            D2D1::Matrix3x2F max = D2D1::Matrix3x2F::Scale(
                D2D1::SizeF(size.Width, size.Height),
                D2D1::Point2F(center.X, center.Y));
            res._11 = max._11;
            res._12 = max._12;
            res._21 = max._21;
            res._22 = max._22;
            res._31 = max._31;
            res._32 = max._32;
            return res;
        }

        /// <summary>拡大・縮小マトリクスを取得する。</summary>
        /// <param name="size">拡大量。</param>
        /// <return>マトリクス。</return>
        static Matrix Scale(System::Drawing::SizeF size)
        {
            Matrix res;
            D2D1::Matrix3x2F max = D2D1::Matrix3x2F::Scale(
                D2D1::SizeF(size.Width, size.Height));
            res._11 = max._11;
            res._12 = max._12;
            res._21 = max._21;
            res._22 = max._22;
            res._31 = max._31;
            res._32 = max._32;
            return res;
        }

        /// <summary>歪みマトリクスを取得する。</summary>
        /// <param name="angleX">X変形角度。</param>
        /// <param name="angleY">Y変形角度。</param>
        /// <param name="center">変形中心。</param>
        /// <return>マトリクス。</return>
        static Matrix Skew(float angleX, float angleY, System::Drawing::PointF center)
        {
            Matrix res;
            D2D1::Matrix3x2F max = D2D1::Matrix3x2F::Skew(
                angleX,
                angleY,
                D2D1::Point2F(center.X, center.Y));
            res._11 = max._11;
            res._12 = max._12;
            res._21 = max._21;
            res._22 = max._22;
            res._31 = max._31;
            res._32 = max._32;
            return res;
        }

        /// <summary>積演算子。</summary>
        /// <param name="left">左辺。</param>
        /// <param name="right">右辺。</param>
        /// <return>マトリクス。</return>
        static Matrix operator*(Matrix left, Matrix right)
        {
            Matrix res;
            D2D1_MATRIX_3X2_F l = left.Convert();
            D2D1_MATRIX_3X2_F r = right.Convert();
            D2D1_MATRIX_3X2_F max = l * r;
            res._11 = max._11;
            res._12 = max._12;
            res._21 = max._21;
            res._22 = max._22;
            res._31 = max._31;
            res._32 = max._32;
            return res;
        }
    };
}