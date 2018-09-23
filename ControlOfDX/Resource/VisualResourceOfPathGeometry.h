#pragma once

#include <vector>
#include "../ControlOfDX.h"
#include "../SingletonFactory.h"
#include "VisualResource.h"

namespace ControlOfDX
{
    using namespace System;
    using namespace System::Drawing;

    /// <summary>パスジオメトリリソース。</summary>
	public ref class VisualResourceOfPathGeometry
		: public VisualResource
	{
#pragma region "inner class"
	public:
        /// <summary>ベジェ曲線セグメント。</summary>
        ref class BezierSegment
        {
        private:
            // 制御点
            PointF pos1, pos2, pos3;

        public:
            /// <summary>コンストラクタ。</summary>
            BezierSegment() {}

            /// <summary>コンストラクタ。</summary>
            /// <param name="p1">制御点1。</param>
            /// <param name="p2">制御点2。</param>
            /// <param name="p3">制御点3。</param>
            BezierSegment(PointF p1, PointF p2, PointF p3)
                : pos1(p1), pos2(p2), pos3(p3) {}

        public:
            /// <summary>制御点1を設定、取得する。</summary>
            property PointF Point1 {
                PointF get() { return this->pos1; }
                void set(PointF pos) { this->pos1 = pos; }
            }

            /// <summary>制御点2を設定、取得する。</summary>
            property PointF Point2 {
                PointF get() { return this->pos2; }
                void set(PointF pos) { this->pos2 = pos; }
            }

            /// <summary>制御点3を設定、取得する。</summary>
            property PointF Point3 {
                PointF get() { return this->pos3; }
                void set(PointF pos) { this->pos3 = pos; }
            }
        };

        /// <summary>円弧セグメント。</summary>
        ref class ArcSegment
        {
        private:
            PointF          point;
            SizeF           size;
            float           rotation;
            SweepDirection  sweep;
            ArcSize         arc;

        public:
            /// <summary>コンストラクタ。</summary>
            ArcSegment() {}

            /// <summary>コンストラクタ。</summary>
            /// <param name="point">弧の終点。</param>
            /// <param name="size">弧のX半径と Y半径。</param>
            /// <param name="rotationAngle">反時計回りに回転する角度。</param>
            /// <param name="sweepDirection">弧の掃引が時計回りか反時計回りかを指定する値。</param>
            /// <param name="arcSize">特定の弧が 180°より大きいかどうかを指定する値。</param>
            ArcSegment(PointF point, SizeF size, float rotationAngle,
                       SweepDirection sweepDirection, ArcSize arcSize)
                : point(point), size(size), rotation(rotationAngle),
                  sweep(sweepDirection), arc(arcSize) {}

        public:
            /// <summary>弧の終点を設定、取得する。</summary>
            property PointF Point {
                PointF get() { return this->point; }
                void set(PointF pos) { this->point = pos; }
            }

            /// <summary>弧のX半径と Y半径を設定、取得する。</summary>
            property SizeF Size {
                SizeF get() { return this->size; }
                void set(SizeF sz) { this->size = sz; }
            }

            /// <summary>反時計回りに回転する角度を設定、取得する。</summary>
            property float RotationAngle {
                float get() { return this->rotation; }
                void set(float rotation) { this->rotation = rotation; }
            }

            /// <summary>弧の掃引が時計回りか反時計回りかを指定する値を設定、取得する。</summary>
            property ControlOfDX::SweepDirection SweepDirection {
                ControlOfDX::SweepDirection get() { return this->sweep; }
                void set(ControlOfDX::SweepDirection rotation) { this->sweep = rotation; }
            }

            /// <summary>特定の弧が 180°より大きいかどうかを指定する値を設定、取得する。</summary>
            property ControlOfDX::ArcSize ArcSize {
                ControlOfDX::ArcSize get() { return this->arc; }
                void set(ControlOfDX::ArcSize rotation) { this->arc = rotation; }
            }
        };

        /// <summary>描画情報を格納するジオメトリシンク。</summary>
		ref class GeometrySink
			: IDisposable
		{
		private:
            // ジオメトリパス
			ID2D1GeometrySink * sink;

		internal:
            /// <summary>コンストラクタ。</summary>
            /// <param name="sink">元になるジオメトリパス。</param>
			GeometrySink(ID2D1GeometrySink * sink) 
				: sink(sink)
			{}

            /// <summary>デストラクタ。</summary>
			~GeometrySink() {
				if (this->sink != NULL) {
					this->sink->Close();
					this->sink->Release();
					this->sink = NULL;
				}
			}

            /// <summary>ファイナライザ。</summary>
			!GeometrySink() {
				this->~GeometrySink();
			}

		public:
            /// <summary>このジオメトリシンクによって記述されたジオメトリの内部にある点と外部にある点を特定するために使用するメソッドを指定します。</summary>
            /// <param name="mode">制御点1。</param>
			void SetFillMode(FillMode mode)
			{
				this->sink->SetFillMode((D2D1_FILL_MODE)mode);
			}

            /// <summary>指定された点から新しい図を開始します。</summary>
            /// <param name="pos">新しい図を開始する点。</param>
            /// <param name="begin">新しい図を塗りつぶすかどうか。</param>
			void BeginFigure(PointF pos, FigureBegin begin)
			{
				this->sink->BeginFigure(D2D1::Point2F(pos.X, pos.Y), (D2D1_FIGURE_BEGIN)begin);
			}

            /// <summary>点を指定して直線を追加する。</summary>
            /// <param name="x">X位置。</param>
            /// <param name="y">Y位置。</param>
            void AddLine(float x, float y)
			{
                this->sink->AddLine(D2D1::Point2F(x, y));
			}

            /// <summary>点を指定して直線を追加する。</summary>
            /// <param name="point">点位置。</param>
            void AddLine(PointF point)
			{
                this->sink->AddLine(D2D1::Point2F(point.X, point.Y));
			}

            /// <summary>点リストを指定して一連の直線を追加する。</summary>
            /// <param name="point">点リスト。</param>
			void AddLines(System::Collections::Generic::IEnumerable<PointF>^ points)
			{
                std::vector<D2D1_POINT_2F> pos;
                for each (PointF p in points) {
                    pos.push_back(D2D1::Point2F(p.X, p.Y));
                }
                this->sink->AddLines(pos.data(), (UINT32)pos.size());
			}

            /// <summary>円弧情報を指定して円弧を追加する。</summary>
            /// <param name="segment">円弧情報。</param>
            void AddArc(ArcSegment ^ segment)
            {
                D2D1_ARC_SEGMENT arc;
                arc.point = D2D1::Point2F(segment->Point.X, segment->Point.Y);
                arc.size = D2D1::SizeF(segment->Size.Width, segment->Size.Height);
                arc.rotationAngle = segment->RotationAngle;
                arc.sweepDirection = (D2D1_SWEEP_DIRECTION)segment->SweepDirection;
                arc.arcSize = (D2D1_ARC_SIZE)segment->ArcSize;
                this->sink->AddArc(arc);
            }

            /// <summary>三点を指定してベジェ曲線を追加する。</summary>
            /// <param name="pos1">点1。</param>
            /// <param name="pos2">点2。</param>
            /// <param name="pos3">点3。</param>
            void AddBezier(PointF pos1, PointF pos2, PointF pos3)
            {
                D2D1_BEZIER_SEGMENT seg = D2D1::BezierSegment(
                    D2D1::Point2F(pos1.X, pos1.Y),
                    D2D1::Point2F(pos2.X, pos2.Y),
                    D2D1::Point2F(pos3.X, pos3.Y)
                );
                this->sink->AddBezier(seg);
            }

            /// <summary>一連の 3次ベジエ曲線を作成してジオメトリシンクに追加します。</summary>
            /// <param name="segment">ベジエ曲線情報。</param>
            void AddBeziers(BezierSegment^ segment)
            {
                D2D1_BEZIER_SEGMENT seg = D2D1::BezierSegment(
                    D2D1::Point2F(segment->Point1.X, segment->Point1.Y),
                    D2D1::Point2F(segment->Point2.X, segment->Point2.Y),
                    D2D1::Point2F(segment->Point3.X, segment->Point3.Y)
                );
                this->sink->AddBezier(&seg);
            }

            /// <summary>一連の 3次ベジエ曲線を作成してジオメトリシンクに追加します。</summary>
            /// <param name="segment">ベジエ曲線情報。</param>
            void AddBeziers(System::Collections::Generic::IEnumerable<BezierSegment^>^ segment)
            {
                std::vector<D2D1_BEZIER_SEGMENT> segs;
                for each (BezierSegment^ segpos in segment) {
                    D2D1_BEZIER_SEGMENT seg = D2D1::BezierSegment(
                        D2D1::Point2F(segpos->Point1.X, segpos->Point1.Y),
                        D2D1::Point2F(segpos->Point2.X, segpos->Point2.Y),
                        D2D1::Point2F(segpos->Point3.X, segpos->Point3.Y)
                    );
                    segs.push_back(seg);
                }
                this->sink->AddBeziers(segs.data(), (UINT32)segs.size());
            }

            /// <summary>現在の図を終了します。必要に応じて、図を閉じることもできます。</summary>
            /// <param name="end">現在の図を閉じるかどうかを示す値。</param>
			void EndFigure(FigureEnd end)
			{
				this->sink->EndFigure((D2D1_FIGURE_END)end);
			}
		};

#pragma endregion

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
			: VisualResource(name)
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
        ID2D1PathGeometry * GetGeometry() {
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
