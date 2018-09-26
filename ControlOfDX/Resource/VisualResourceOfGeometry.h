#pragma once

#include <vector>
#include "../ControlOfDX.h"
#include "VisualResource.h"
#include "VisualResourceOfPathGeometry.h"

namespace ControlOfDX
{
    /// <summary>ジオメトリリソースインターフェース。</summary>
    public ref class VisualResourceOfGeometry abstract
        : VisualResource
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
            : public IDisposable
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

        internal:
            /// <summary>ジオメトリシンクを取得する。</summary>
            /// <return>ジオメトリシンク。</return>
            ID2D1GeometrySink * GetSink()
            {
                return this->sink;
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

            /// <summary>円弧情報を指定して円弧を追加する。</summary>    
            /// <param name="point">弧の終点。</param>
            /// <param name="size">弧のX半径とY半径。</param>
            /// <param name="rotationAngle">反時計回りに回転する角度。</param>
            /// <param name="sweepDirection">時計回りか反時計回りかを指定する。</param>
            /// <param name="arcSize">特定の弧が 180°より大きいか指定する。</param>
            void AddArc(PointF point, SizeF size, float rotationAngle, SweepDirection sweepDirection, ArcSize arcSize)
            {
                D2D1_ARC_SEGMENT arc;
                arc.point = D2D1::Point2F(point.X, point.Y);
                arc.size = D2D1::SizeF(size.Width, size.Height);
                arc.rotationAngle = rotationAngle;
                arc.sweepDirection = (D2D1_SWEEP_DIRECTION)sweepDirection;
                arc.arcSize = (D2D1_ARC_SIZE)arcSize;
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

        /// <summary>ComputePointAtLength用、戻り値。</summary>
        value class PointAtLength
        {
        public:
            /// <summary>ジオメトリに沿って指定された距離だけ離れた位置。ジオメトリが空の場合、この点にはその X と Y の値として NaN が格納されます。</summary>
            PointF point;

            /// <summary>このメソッドが返されるときに、ジオメトリに沿って指定された距離だけ離れた位置にある接線ベクトルへのポインターが格納されます。ジオメトリが空の場合、このベクトルにはその X と Y の値として NaN が格納されます。このパラメーターに記憶域を割り当てる必要があります。</summary>
            PointF unitTangentVector;
        };

#pragma endregion

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


    public:
        /// <summary>このジオメトリを指定されたジオメトリと結合して、その結果をパスジオメトリに格納します。</summary>
        /// <param name="inputGeometry">結合するジオメトリ。</param>
        /// <param name="combineMode">実行する結合操作の種類。</param>
        /// <param name="geometrySink ">結合操作の結果。</param>
        void CombineWithGeometry(VisualResourceOfGeometry ^ inputGeometry,
                                 CombineMode combineMode,
                                 GeometrySink ^ geometrySink)
        {
            this->GetGeometry()->CombineWithGeometry(inputGeometry->GetGeometry(),
                (D2D1_COMBINE_MODE)combineMode, 0, 0, geometrySink->GetSink());
        }

        /// <summary>このジオメトリを指定されたジオメトリと結合して、その結果をパスジオメトリに格納します。</summary>
        /// <param name="inputGeometry">結合するジオメトリ。</param>
        /// <param name="combineMode">実行する結合操作の種類。</param>
        /// <param name="inputGeometryTransform">結合前にジオメトリに適用する変換。</param>
        /// <param name="geometrySink ">結合操作の結果。</param>
        void CombineWithGeometry(VisualResourceOfGeometry ^ inputGeometry,
                                 CombineMode combineMode,
                                 Matrix inputGeometryTransform,
                                 GeometrySink ^ geometrySink)
        {
            D2D1_MATRIX_3X2_F matrix = inputGeometryTransform.Convert();
            this->GetGeometry()->CombineWithGeometry(inputGeometry->GetGeometry(),
                (D2D1_COMBINE_MODE)combineMode, &matrix, 0, geometrySink->GetSink());
        }

        /// <summary>このジオメトリを指定されたジオメトリと結合して、その結果をパスジオメトリに格納します。</summary>
        /// <param name="inputGeometry">結合するジオメトリ。</param>
        /// <param name="combineMode">実行する結合操作の種類。</param>
        /// <param name="inputGeometryTransform">結合前にジオメトリに適用する変換。</param>
        /// <param name="flatteningTolerance">ジオメトリの多角形近似における点と点の間の距離の上限。値が小さいほど、生成される結果の精度は高くなりますが、実行速度は低下します。</param>
        /// <param name="geometrySink ">結合操作の結果。</param>
        void CombineWithGeometry(VisualResourceOfGeometry ^ inputGeometry,
                                 CombineMode combineMode,
                                 Matrix inputGeometryTransform,
                                 float flatteningTolerance,
                                 GeometrySink ^ geometrySink)
        {
            D2D1_MATRIX_3X2_F matrix = inputGeometryTransform.Convert();
            this->GetGeometry()->CombineWithGeometry(inputGeometry->GetGeometry(),
                (D2D1_COMBINE_MODE)combineMode, &matrix, flatteningTolerance, geometrySink->GetSink());
        }

        /// <summary>このジオメトリと指定されたジオメトリとの間の交差点を記述します。</summary>
        /// <param name="inputGeometry">テストするジオメトリ。</param>
        /// <param name="inputGeometryTransform">その領域を計算する前にこのジオメトリに適用される変換。</param>
        /// <return>どのように関連しているかを示す値。</return>
        GeometryRelation CompareWithGeometry(VisualResourceOfGeometry ^ inputGeometry,
                                             Matrix inputGeometryTransform)
        {
            D2D1_GEOMETRY_RELATION result = D2D1_GEOMETRY_RELATION_UNKNOWN;
            D2D1_MATRIX_3X2_F matrix = inputGeometryTransform.Convert();
            HRESULT hr = this->GetGeometry()->CompareWithGeometry(inputGeometry->GetGeometry(), matrix, &result);
            return (SUCCEEDED(hr) ? (GeometryRelation)result : GeometryRelation::GEOMETRY_RELATION_UNKNOWN);
        }

        /// <summary>このジオメトリと指定されたジオメトリとの間の交差点を記述します。</summary>
        /// <param name="inputGeometry">テストするジオメトリ。</param>
        /// <param name="inputGeometryTransform">その領域を計算する前にこのジオメトリに適用される変換。</param>
        /// <param name="flatteningTolerance">ジオメトリの多角形近似を構築するときに許容される最大誤差。</param>
        /// <return>どのように関連しているかを示す値。</return>
        GeometryRelation CompareWithGeometry(VisualResourceOfGeometry ^ inputGeometry,
                                             Matrix inputGeometryTransform,
                                             float flatteningTolerance)
        {
            D2D1_GEOMETRY_RELATION result = D2D1_GEOMETRY_RELATION_UNKNOWN;
            D2D1_MATRIX_3X2_F matrix = inputGeometryTransform.Convert();
            HRESULT hr = this->GetGeometry()->CompareWithGeometry(inputGeometry->GetGeometry(), matrix, flatteningTolerance, &result);
            return (SUCCEEDED(hr) ? (GeometryRelation)result : GeometryRelation::GEOMETRY_RELATION_UNKNOWN);
        }

        /// <summary>ジオメトリが指定された行列で変換され、デフォルトの公差を使用して平坦化された後のジオメトリの領域を計算します。</summary>
        /// <param name="inputGeometryTransform">その領域を計算する前にこのジオメトリに適用される変換。</param>
        /// <return>ジオメトリの領域。</return>
        float ComputeArea(Matrix inputGeometryTransform)
        {
            float area;
            D2D1_MATRIX_3X2_F matrix = inputGeometryTransform.Convert();
            HRESULT hr = this->GetGeometry()->ComputeArea(matrix, &area);
            return (SUCCEEDED(hr) ? area : -1);
        }

        /// <summary>各セグメントがラインに展開されているかのように、ジオメトリの長さを計算します。</summary>
        /// <param name="inputGeometryTransform">その領域を計算する前にこのジオメトリに適用される変換。</param>
        /// <return>ジオメトリの長さ。</return>
        float ComputeLength(Matrix inputGeometryTransform)
        {
            float length;
            D2D1_MATRIX_3X2_F matrix = inputGeometryTransform.Convert();
            HRESULT hr = this->GetGeometry()->ComputeLength(matrix, &length);
            return (SUCCEEDED(hr) ? length : -1);
        }

        /// <summary>ジオメトリが指定された行列で変換され、既定の許容範囲でフラット化された後、そのジオメトリに沿って指定された距離だけ離れた位置にある点と接線ベクトルを計算します。</summary>
        /// <param name="length">検出される点と接線までのジオメトリに沿った距離。</param>
        /// <param name="worldTransform">指定された点と接線を計算する前にジオメトリに適用する変換。</param>
        /// <return>点と接線ベクトル。</return>
        PointAtLength ComputePointAtLength(float length, Matrix worldTransform)
        {
            PointAtLength res;
            D2D1_MATRIX_3X2_F matrix = worldTransform.Convert();
            D2D1_POINT_2F point;
            D2D1_POINT_2F unitTangentVector;

            HRESULT hr = this->GetGeometry()->ComputePointAtLength(length, &matrix, &point, &unitTangentVector);
            if (SUCCEEDED(hr)) {
                res.point.X = point.x;
                res.point.Y = point.y;
                res.unitTangentVector.X = unitTangentVector.x;
                res.unitTangentVector.Y = unitTangentVector.y;
            }
            else {
                res.point.X = float::NaN;
                res.point.Y = float::NaN;
                res.unitTangentVector.X = float::NaN;
                res.unitTangentVector.Y = float::NaN;
            }
            return res;
        }

        /// <summary>ジオメトリが指定された行列で変換され、既定の許容範囲でフラット化された後、そのジオメトリに沿って指定された距離だけ離れた位置にある点と接線ベクトルを計算します。</summary>
        /// <param name="length">検出される点と接線までのジオメトリに沿った距離。</param>
        /// <return>点と接線ベクトル。</return>
        PointAtLength ComputePointAtLength(float length)
        {
            PointAtLength res;
            D2D1_POINT_2F point;
            D2D1_POINT_2F unitTangentVector;

            HRESULT hr = this->GetGeometry()->ComputePointAtLength(length, 0, &point, &unitTangentVector);
            if (SUCCEEDED(hr)) {
                res.point.X = point.x;
                res.point.Y = point.y;
                res.unitTangentVector.X = unitTangentVector.x;
                res.unitTangentVector.Y = unitTangentVector.y;
            }
            else {
                res.point.X = float::NaN;
                res.point.Y = float::NaN;
                res.unitTangentVector.X = float::NaN;
                res.unitTangentVector.Y = float::NaN;
            }
            return res;
        }

        /*
        void ooo()
        {
            this->GetGeometry()->FillContainsPoint;
            this->GetGeometry()->GetBounds;
            this->GetGeometry()->GetFactory();
            this->GetGeometry()->GetWidenedBounds();
            this->GetGeometry()->Outline();
            this->GetGeometry()->QueryInterface();
            this->GetGeometry()->Simplify();
            this->GetGeometry()->StrokeContainsPoint();
            this->GetGeometry()->Tessellate();
            this->GetGeometry()->Widen();
        }
        */

#pragma endregion

	};
}
