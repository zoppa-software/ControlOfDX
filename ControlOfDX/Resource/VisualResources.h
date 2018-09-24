#pragma once

#include "../ControlOfDX.h"
#include "../SingletonFactory.h"
#include "VisualResource.h"
#include "VisualResourceOfSolidColorBrush.h"
#include "VisualResourceOfPathGeometry.h"
#include "VisualResourceOfBitmap.h"
#include "VisualResourceOfBitmapBrush.h"
#include "VisualResourceOfD2BitmapBrush.h"
#include "VisualResourceOfLineGradientBrush.h"
#include "VisualResourceOfRadialGradientBrush.h"
#include "VisualResourceOfTextFormat.h"
#include "VisualResourceOfStrokeStyle.h"
#include "VisualResourceOfEllipseGeometry.h"
#include "VisualResourceOfRectangleGeometry.h"
#include "VisualResourceOfTransformedGeometry.h"

namespace ControlOfDX
{
    using namespace System;
    using namespace System::Collections::Generic;

    /// <summary>リソース・コレクション。</summary>
	public ref class VisualResources sealed
	{
#pragma region "fields"
    private:
        /// <summary>リソース・テーブル。</summary>
        SortedDictionary<String ^, VisualResource ^>^ items;

#pragma endregion

#pragma region "properties"
    public:
        /// <summary>登録しているリソース数を取得する。</summary>
        /// <return>リソース数。</return>
        property int Count
        {
            int get() {
                return this->items->Count;
            }
        }

        /// <summary>名前を指定してリソースを取得する。</summary>
        /// <param name="name">リソース名。</param>
        /// <return>リソース。</return>
        property VisualResource ^ default[String^]
        {
            VisualResource ^ get(String^ name) {
                VisualResource ^ val;
                return (this->items->TryGetValue(name, val) ? val : nullptr);
            }
        }

        /// <summary>リソース名を列挙する。</summary>
        property SortedDictionary<String ^, VisualResource ^>::KeyCollection ^ Keys
        {
            SortedDictionary<String ^, VisualResource ^>::KeyCollection ^ get() {
                return this->items->Keys;
            }
        }

        /// <summary>リソースを列挙する。</summary>
        property SortedDictionary<String ^, VisualResource ^>::ValueCollection ^ Values
        {
            SortedDictionary<String ^, VisualResource ^>::ValueCollection ^ get() {
                return this->items->Values;
            }
        }

#pragma endregion

#pragma region "constructor/destructor"
	public:
        /// <summary>コンストラクタ。</summary>
        VisualResources()
        {
            this->items = gcnew SortedDictionary<String ^, VisualResource ^>();
        }

#pragma endregion

#pragma region "methods"
	public:
        /// <summary>全てのリソースを削除する。</summary>
        void Clear()
        {
            this->items->Clear();
        }

        /// <summary>指定名のリソースを保持していたら真を返す。</summary>
        /// <param name="name">リソース名。</param>
        /// <return>リソースを持っていたら真。</return>
        bool HasResource(String^ name)
        {
            return this->items->ContainsKey(name);
        }

        /// <summary>指定名のリソースを削除する。</summary>
        /// <param name="name">削除するリソース名。</param>
        void Remove(String ^ name)
        {
            if (this->items->ContainsKey(name)) {
                delete this->items[name];
                this->items->Remove(name);
            }
        }

    private:
        /// <summary>リソースを追加する。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="resource">追加するリソース。</param>
        void Add(String ^ name, VisualResource ^ resource)
        {
            this->items->Add(name, resource);
        }

    public:
        //-------------------------------------------------------------------------
        // リソース作成
        //-------------------------------------------------------------------------
        /// <summary>ソリッドカラーブラシを作成する。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="red">赤色成分。</param>
        /// <param name="green">緑色成分。</param>
        /// <param name="blue">青色成分。</param>
        /// <param name="alpha">透明成分。</param>
        /// <return>リソース。</return>
        VisualResourceOfSolidColorBrush ^ CreateSolidColorBrush(String ^ name, int red, int green, int blue, int alpha)
        {
            VisualResourceOfSolidColorBrush ^ res = gcnew VisualResourceOfSolidColorBrush(name, red, green, blue, alpha);
            this->items->Add(res->Name, res);
            return res;
        }

        /// <summary>ソリッドカラーブラシを作成する。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="color">ブラシの色。</param>
        /// <return>リソース。</return>
        VisualResourceOfSolidColorBrush ^ CreateSolidColorBrush(String ^ name, Color color)
        {
            VisualResourceOfSolidColorBrush ^ res = gcnew VisualResourceOfSolidColorBrush(name, color.R, color.G, color.B, color.A);
            this->items->Add(res->Name, res);
            return res;
        }

        /// <summary>ジオメトリを作成する。</summary>
        /// <param name="name">リソース名。</param>
        /// <return>リソース。</return>
        VisualResourceOfPathGeometry ^ CreatePathGeometry(String ^ name)
        {
            VisualResourceOfPathGeometry ^ res = gcnew VisualResourceOfPathGeometry(name);
            this->items->Add(res->Name, res);
            return res;
        }

        /// <summary>円形ジオメトリを作成する。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="ellipse">楕円情報。</param>
        /// <return>リソース。</return>
        VisualResourceOfEllipseGeometry ^ CreateEllipseGeometry(String ^ name, Ellipse ellipse)
        {
            VisualResourceOfEllipseGeometry ^ res = gcnew VisualResourceOfEllipseGeometry(name, ellipse);
            this->items->Add(res->Name, res);
            return res;
        }

        /// <summary>円形ジオメトリを作成する。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="center">中心位置。</param>
        /// <param name = "radiusX">楕円 X半径。< / param>
        /// <param name = "radiusY">楕円 Y半径。< / param>
        /// <return>リソース。</return>
        VisualResourceOfEllipseGeometry ^ CreateEllipseGeometry(String ^ name, PointF center, float radiusX, float radiusY)
        {
            VisualResourceOfEllipseGeometry ^ res = gcnew VisualResourceOfEllipseGeometry(name, center, radiusX, radiusY);
            this->items->Add(res->Name, res);
            return res;
        }

        /// <summary>ビットマップを作成する。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="bitmap">元としたビットマップ。</param>
        /// <return>リソース。</return>
        VisualResourceOfBitmap ^ CreateBitmap(String ^ name, Bitmap ^ bitmap)
        {
            VisualResourceOfBitmap ^ res = gcnew VisualResourceOfBitmap(name, bitmap);
            this->items->Add(res->Name, res);
            return res;
        }

        /// <summary>ビットマップブラシを作成する。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="bitmap">ブラシに使用するビットマップ。</param>
        /// <return>リソース。</return>
        VisualResourceOfBitmapBrush ^ CreateBitmapBrush(String ^ name, Bitmap ^ bitmap)
        {
            VisualResourceOfBitmapBrush ^ res = gcnew VisualResourceOfBitmapBrush(name, bitmap);
            this->items->Add(res->Name, res);
            return res;
        }

        /// <summary>ビットマップブラシを作成する。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="bitmap">ブラシに使用するビットマップ。</param>
        /// <return>リソース。</return>
        VisualResourceOfD2BitmapBrush ^ CreateBitmapBrush(String ^ name, VisualResourceOfBitmap ^ bitmap)
        {
            VisualResourceOfD2BitmapBrush ^ res = gcnew VisualResourceOfD2BitmapBrush(name, bitmap);
            this->items->Add(res->Name, res);
            return res;
        }

        /// <summary>ライングラデーションブラシを作成する。</summary>
        /// <param name="name">リソース名。</param>
        /// <return>リソース。</return>
        VisualResourceOfLinearGradientBrush ^ CreateLinearGradientBrush(String ^ name)
        {
            VisualResourceOfLinearGradientBrush ^ res = gcnew VisualResourceOfLinearGradientBrush(name);
            this->items->Add(res->Name, res);
            return res;
        }

        /// <summary>放射グラデーションブラシを作成する。</summary>
        /// <param name="name">リソース名。</param>
        /// <return>リソース。</return>
        VisualResourceOfRadialGradientBrush ^ CreateRadialGradientBrush(String ^ name)
        {
            VisualResourceOfRadialGradientBrush ^ res = gcnew VisualResourceOfRadialGradientBrush(name);
            this->items->Add(res->Name, res);
            return res;
        }

        /// <summary>文字列書式リソースを作成する。</summary>
        /// <param name="name">リソース名。</param>
        /// <return>リソース。</return>
        VisualResourceOfTextFormat ^ CreateTextFormat(String ^ name)
        {
            VisualResourceOfTextFormat ^ res = gcnew VisualResourceOfTextFormat(name);
            this->items->Add(res->Name, res);
            return res;
        }

        /// <summary>ストロークスタイルを作成する。</summary>
        /// <param name="name">リソース名。</param>
        /// <return>リソース。</return>
        VisualResourceOfStrokeStyle ^ CreateStrokeStyle(String ^ name)
        {
            VisualResourceOfStrokeStyle ^ res = gcnew VisualResourceOfStrokeStyle(name);
            this->items->Add(res->Name, res);
            return res;
        }

        /// <summary>矩形ジオメトリリソースを作成する。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="rectangle">作成する矩形。</param>
        /// <return>リソース。</return>
        VisualResourceOfRectangleGeometry ^ CreateRectangleGeometry(String ^ name, RectangleF rectangle)
        {
            VisualResourceOfRectangleGeometry ^ res = gcnew VisualResourceOfRectangleGeometry(name, rectangle);
            this->items->Add(res->Name, res);
            return res;
        }

        /// <summary>変形ジオメトリリソースを作成する。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="pathGeometry">変形するジオメトリ。</param>
        /// <param name="matrix">変形マトリクス。</param>
        /// <return>リソース。</return>
        VisualResourceOfTransformedGeometry ^ CreateTransformedGeometry(String ^ name,
                                                                        VisualResourceOfPathGeometry ^ pathGeometry,
                                                                        Matrix matrix)
        {
            VisualResourceOfTransformedGeometry ^ res = gcnew VisualResourceOfTransformedGeometry(name, pathGeometry, matrix);
            this->items->Add(res->Name, res);
            return res;
        }

#pragma endregion
	};
}