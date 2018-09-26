#pragma once

#include <vector>
#include "../ControlOfDX.h"
#include "VisualResource.h"
#include "VisualResourceOfPathGeometry.h"

namespace ControlOfDX
{
    /// <summary>�W�I���g�����\�[�X�C���^�[�t�F�[�X�B</summary>
    public ref class VisualResourceOfGeometry abstract
        : VisualResource
	{
#pragma region "inner class"
    public:
        /// <summary>�x�W�F�Ȑ��Z�O�����g�B</summary>
        ref class BezierSegment
        {
        private:
            // ����_
            PointF pos1, pos2, pos3;

        public:
            /// <summary>�R���X�g���N�^�B</summary>
            BezierSegment() {}

            /// <summary>�R���X�g���N�^�B</summary>
            /// <param name="p1">����_1�B</param>
            /// <param name="p2">����_2�B</param>
            /// <param name="p3">����_3�B</param>
            BezierSegment(PointF p1, PointF p2, PointF p3)
                : pos1(p1), pos2(p2), pos3(p3) {}

        public:
            /// <summary>����_1��ݒ�A�擾����B</summary>
            property PointF Point1 {
                PointF get() { return this->pos1; }
                void set(PointF pos) { this->pos1 = pos; }
            }

            /// <summary>����_2��ݒ�A�擾����B</summary>
            property PointF Point2 {
                PointF get() { return this->pos2; }
                void set(PointF pos) { this->pos2 = pos; }
            }

            /// <summary>����_3��ݒ�A�擾����B</summary>
            property PointF Point3 {
                PointF get() { return this->pos3; }
                void set(PointF pos) { this->pos3 = pos; }
            }
        };

        /// <summary>�~�ʃZ�O�����g�B</summary>
        ref class ArcSegment
        {
        private:
            PointF          point;
            SizeF           size;
            float           rotation;
            SweepDirection  sweep;
            ArcSize         arc;

        public:
            /// <summary>�R���X�g���N�^�B</summary>
            ArcSegment() {}

            /// <summary>�R���X�g���N�^�B</summary>
            /// <param name="point">�ʂ̏I�_�B</param>
            /// <param name="size">�ʂ�X���a�� Y���a�B</param>
            /// <param name="rotationAngle">�����v���ɉ�]����p�x�B</param>
            /// <param name="sweepDirection">�ʂ̑|�������v��肩�����v��肩���w�肷��l�B</param>
            /// <param name="arcSize">����̌ʂ� 180�����傫�����ǂ������w�肷��l�B</param>
            ArcSegment(PointF point, SizeF size, float rotationAngle,
                SweepDirection sweepDirection, ArcSize arcSize)
                : point(point), size(size), rotation(rotationAngle),
                sweep(sweepDirection), arc(arcSize) {}

        public:
            /// <summary>�ʂ̏I�_��ݒ�A�擾����B</summary>
            property PointF Point {
                PointF get() { return this->point; }
                void set(PointF pos) { this->point = pos; }
            }

            /// <summary>�ʂ�X���a�� Y���a��ݒ�A�擾����B</summary>
            property SizeF Size {
                SizeF get() { return this->size; }
                void set(SizeF sz) { this->size = sz; }
            }

            /// <summary>�����v���ɉ�]����p�x��ݒ�A�擾����B</summary>
            property float RotationAngle {
                float get() { return this->rotation; }
                void set(float rotation) { this->rotation = rotation; }
            }

            /// <summary>�ʂ̑|�������v��肩�����v��肩���w�肷��l��ݒ�A�擾����B</summary>
            property ControlOfDX::SweepDirection SweepDirection {
                ControlOfDX::SweepDirection get() { return this->sweep; }
                void set(ControlOfDX::SweepDirection rotation) { this->sweep = rotation; }
            }

            /// <summary>����̌ʂ� 180�����傫�����ǂ������w�肷��l��ݒ�A�擾����B</summary>
            property ControlOfDX::ArcSize ArcSize {
                ControlOfDX::ArcSize get() { return this->arc; }
                void set(ControlOfDX::ArcSize rotation) { this->arc = rotation; }
            }
        };

        /// <summary>�`������i�[����W�I���g���V���N�B</summary>
        ref class GeometrySink
            : public IDisposable
        {
        private:
            // �W�I���g���p�X
            ID2D1GeometrySink * sink;

        internal:
            /// <summary>�R���X�g���N�^�B</summary>
            /// <param name="sink">���ɂȂ�W�I���g���p�X�B</param>
            GeometrySink(ID2D1GeometrySink * sink)
                : sink(sink)
            {}

            /// <summary>�f�X�g���N�^�B</summary>
            ~GeometrySink() {
                if (this->sink != NULL) {
                    this->sink->Close();
                    this->sink->Release();
                    this->sink = NULL;
                }
            }

            /// <summary>�t�@�C�i���C�U�B</summary>
            !GeometrySink() {
                this->~GeometrySink();
            }

        internal:
            /// <summary>�W�I���g���V���N���擾����B</summary>
            /// <return>�W�I���g���V���N�B</return>
            ID2D1GeometrySink * GetSink()
            {
                return this->sink;
            }

        public:
            /// <summary>���̃W�I���g���V���N�ɂ���ċL�q���ꂽ�W�I���g���̓����ɂ���_�ƊO���ɂ���_����肷�邽�߂Ɏg�p���郁�\�b�h���w�肵�܂��B</summary>
            /// <param name="mode">����_1�B</param>
            void SetFillMode(FillMode mode)
            {
                this->sink->SetFillMode((D2D1_FILL_MODE)mode);
            }

            /// <summary>�w�肳�ꂽ�_����V�����}���J�n���܂��B</summary>
            /// <param name="pos">�V�����}���J�n����_�B</param>
            /// <param name="begin">�V�����}��h��Ԃ����ǂ����B</param>
            void BeginFigure(PointF pos, FigureBegin begin)
            {
                this->sink->BeginFigure(D2D1::Point2F(pos.X, pos.Y), (D2D1_FIGURE_BEGIN)begin);
            }

            /// <summary>�_���w�肵�Ē�����ǉ�����B</summary>
            /// <param name="x">X�ʒu�B</param>
            /// <param name="y">Y�ʒu�B</param>
            void AddLine(float x, float y)
            {
                this->sink->AddLine(D2D1::Point2F(x, y));
            }

            /// <summary>�_���w�肵�Ē�����ǉ�����B</summary>
            /// <param name="point">�_�ʒu�B</param>
            void AddLine(PointF point)
            {
                this->sink->AddLine(D2D1::Point2F(point.X, point.Y));
            }

            /// <summary>�_���X�g���w�肵�Ĉ�A�̒�����ǉ�����B</summary>
            /// <param name="point">�_���X�g�B</param>
            void AddLines(System::Collections::Generic::IEnumerable<PointF>^ points)
            {
                std::vector<D2D1_POINT_2F> pos;
                for each (PointF p in points) {
                    pos.push_back(D2D1::Point2F(p.X, p.Y));
                }
                this->sink->AddLines(pos.data(), (UINT32)pos.size());
            }

            /// <summary>�~�ʏ����w�肵�ĉ~�ʂ�ǉ�����B</summary>
            /// <param name="segment">�~�ʏ��B</param>
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

            /// <summary>�~�ʏ����w�肵�ĉ~�ʂ�ǉ�����B</summary>    
            /// <param name="point">�ʂ̏I�_�B</param>
            /// <param name="size">�ʂ�X���a��Y���a�B</param>
            /// <param name="rotationAngle">�����v���ɉ�]����p�x�B</param>
            /// <param name="sweepDirection">���v��肩�����v��肩���w�肷��B</param>
            /// <param name="arcSize">����̌ʂ� 180�����傫�����w�肷��B</param>
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

            /// <summary>�O�_���w�肵�ăx�W�F�Ȑ���ǉ�����B</summary>
            /// <param name="pos1">�_1�B</param>
            /// <param name="pos2">�_2�B</param>
            /// <param name="pos3">�_3�B</param>
            void AddBezier(PointF pos1, PointF pos2, PointF pos3)
            {
                D2D1_BEZIER_SEGMENT seg = D2D1::BezierSegment(
                    D2D1::Point2F(pos1.X, pos1.Y),
                    D2D1::Point2F(pos2.X, pos2.Y),
                    D2D1::Point2F(pos3.X, pos3.Y)
                );
                this->sink->AddBezier(seg);
            }

            /// <summary>��A�� 3���x�W�G�Ȑ����쐬���ăW�I���g���V���N�ɒǉ����܂��B</summary>
            /// <param name="segment">�x�W�G�Ȑ����B</param>
            void AddBeziers(BezierSegment^ segment)
            {
                D2D1_BEZIER_SEGMENT seg = D2D1::BezierSegment(
                    D2D1::Point2F(segment->Point1.X, segment->Point1.Y),
                    D2D1::Point2F(segment->Point2.X, segment->Point2.Y),
                    D2D1::Point2F(segment->Point3.X, segment->Point3.Y)
                );
                this->sink->AddBezier(&seg);
            }

            /// <summary>��A�� 3���x�W�G�Ȑ����쐬���ăW�I���g���V���N�ɒǉ����܂��B</summary>
            /// <param name="segment">�x�W�G�Ȑ����B</param>
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

            /// <summary>���݂̐}���I�����܂��B�K�v�ɉ����āA�}����邱�Ƃ��ł��܂��B</summary>
            /// <param name="end">���݂̐}����邩�ǂ����������l�B</param>
            void EndFigure(FigureEnd end)
            {
                this->sink->EndFigure((D2D1_FIGURE_END)end);
            }
        };

        /// <summary>ComputePointAtLength�p�A�߂�l�B</summary>
        value class PointAtLength
        {
        public:
            /// <summary>�W�I���g���ɉ����Ďw�肳�ꂽ�����������ꂽ�ʒu�B�W�I���g������̏ꍇ�A���̓_�ɂ͂��� X �� Y �̒l�Ƃ��� NaN ���i�[����܂��B</summary>
            PointF point;

            /// <summary>���̃��\�b�h���Ԃ����Ƃ��ɁA�W�I���g���ɉ����Ďw�肳�ꂽ�����������ꂽ�ʒu�ɂ���ڐ��x�N�g���ւ̃|�C���^�[���i�[����܂��B�W�I���g������̏ꍇ�A���̃x�N�g���ɂ͂��� X �� Y �̒l�Ƃ��� NaN ���i�[����܂��B���̃p�����[�^�[�ɋL��������蓖�Ă�K�v������܂��B</summary>
            PointF unitTangentVector;
        };

#pragma endregion

#pragma region "constructor/destructor"
    public:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="name">���\�[�X���B</param>
        VisualResourceOfGeometry(String ^ name)
            : VisualResource(name)
        {}

        /// <summary>�f�X�g���N�^�B</summary>
        virtual ~VisualResourceOfGeometry() {}

        /// <summary>�t�@�C�i���C�U�B</summary>
        !VisualResourceOfGeometry() {}

#pragma endregion

#pragma region "methods"
    internal:
        /// <summary>�W�I���g���̎��̂��擾����B</summary>
        /// <return>�W�I���g���B</return>
        virtual ID2D1Geometry * GetGeometry() = 0;


    public:
        /// <summary>���̃W�I���g�����w�肳�ꂽ�W�I���g���ƌ������āA���̌��ʂ��p�X�W�I���g���Ɋi�[���܂��B</summary>
        /// <param name="inputGeometry">��������W�I���g���B</param>
        /// <param name="combineMode">���s���錋������̎�ށB</param>
        /// <param name="geometrySink ">��������̌��ʁB</param>
        void CombineWithGeometry(VisualResourceOfGeometry ^ inputGeometry,
                                 CombineMode combineMode,
                                 GeometrySink ^ geometrySink)
        {
            this->GetGeometry()->CombineWithGeometry(inputGeometry->GetGeometry(),
                (D2D1_COMBINE_MODE)combineMode, 0, 0, geometrySink->GetSink());
        }

        /// <summary>���̃W�I���g�����w�肳�ꂽ�W�I���g���ƌ������āA���̌��ʂ��p�X�W�I���g���Ɋi�[���܂��B</summary>
        /// <param name="inputGeometry">��������W�I���g���B</param>
        /// <param name="combineMode">���s���錋������̎�ށB</param>
        /// <param name="inputGeometryTransform">�����O�ɃW�I���g���ɓK�p����ϊ��B</param>
        /// <param name="geometrySink ">��������̌��ʁB</param>
        void CombineWithGeometry(VisualResourceOfGeometry ^ inputGeometry,
                                 CombineMode combineMode,
                                 Matrix inputGeometryTransform,
                                 GeometrySink ^ geometrySink)
        {
            D2D1_MATRIX_3X2_F matrix = inputGeometryTransform.Convert();
            this->GetGeometry()->CombineWithGeometry(inputGeometry->GetGeometry(),
                (D2D1_COMBINE_MODE)combineMode, &matrix, 0, geometrySink->GetSink());
        }

        /// <summary>���̃W�I���g�����w�肳�ꂽ�W�I���g���ƌ������āA���̌��ʂ��p�X�W�I���g���Ɋi�[���܂��B</summary>
        /// <param name="inputGeometry">��������W�I���g���B</param>
        /// <param name="combineMode">���s���錋������̎�ށB</param>
        /// <param name="inputGeometryTransform">�����O�ɃW�I���g���ɓK�p����ϊ��B</param>
        /// <param name="flatteningTolerance">�W�I���g���̑��p�`�ߎ��ɂ�����_�Ɠ_�̊Ԃ̋����̏���B�l���������قǁA��������錋�ʂ̐��x�͍����Ȃ�܂����A���s���x�͒ቺ���܂��B</param>
        /// <param name="geometrySink ">��������̌��ʁB</param>
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

        /// <summary>���̃W�I���g���Ǝw�肳�ꂽ�W�I���g���Ƃ̊Ԃ̌����_���L�q���܂��B</summary>
        /// <param name="inputGeometry">�e�X�g����W�I���g���B</param>
        /// <param name="inputGeometryTransform">���̗̈���v�Z����O�ɂ��̃W�I���g���ɓK�p�����ϊ��B</param>
        /// <return>�ǂ̂悤�Ɋ֘A���Ă��邩�������l�B</return>
        GeometryRelation CompareWithGeometry(VisualResourceOfGeometry ^ inputGeometry,
                                             Matrix inputGeometryTransform)
        {
            D2D1_GEOMETRY_RELATION result = D2D1_GEOMETRY_RELATION_UNKNOWN;
            D2D1_MATRIX_3X2_F matrix = inputGeometryTransform.Convert();
            HRESULT hr = this->GetGeometry()->CompareWithGeometry(inputGeometry->GetGeometry(), matrix, &result);
            return (SUCCEEDED(hr) ? (GeometryRelation)result : GeometryRelation::GEOMETRY_RELATION_UNKNOWN);
        }

        /// <summary>���̃W�I���g���Ǝw�肳�ꂽ�W�I���g���Ƃ̊Ԃ̌����_���L�q���܂��B</summary>
        /// <param name="inputGeometry">�e�X�g����W�I���g���B</param>
        /// <param name="inputGeometryTransform">���̗̈���v�Z����O�ɂ��̃W�I���g���ɓK�p�����ϊ��B</param>
        /// <param name="flatteningTolerance">�W�I���g���̑��p�`�ߎ����\�z����Ƃ��ɋ��e�����ő�덷�B</param>
        /// <return>�ǂ̂悤�Ɋ֘A���Ă��邩�������l�B</return>
        GeometryRelation CompareWithGeometry(VisualResourceOfGeometry ^ inputGeometry,
                                             Matrix inputGeometryTransform,
                                             float flatteningTolerance)
        {
            D2D1_GEOMETRY_RELATION result = D2D1_GEOMETRY_RELATION_UNKNOWN;
            D2D1_MATRIX_3X2_F matrix = inputGeometryTransform.Convert();
            HRESULT hr = this->GetGeometry()->CompareWithGeometry(inputGeometry->GetGeometry(), matrix, flatteningTolerance, &result);
            return (SUCCEEDED(hr) ? (GeometryRelation)result : GeometryRelation::GEOMETRY_RELATION_UNKNOWN);
        }

        /// <summary>�W�I���g�����w�肳�ꂽ�s��ŕϊ�����A�f�t�H���g�̌������g�p���ĕ��R�����ꂽ��̃W�I���g���̗̈���v�Z���܂��B</summary>
        /// <param name="inputGeometryTransform">���̗̈���v�Z����O�ɂ��̃W�I���g���ɓK�p�����ϊ��B</param>
        /// <return>�W�I���g���̗̈�B</return>
        float ComputeArea(Matrix inputGeometryTransform)
        {
            float area;
            D2D1_MATRIX_3X2_F matrix = inputGeometryTransform.Convert();
            HRESULT hr = this->GetGeometry()->ComputeArea(matrix, &area);
            return (SUCCEEDED(hr) ? area : -1);
        }

        /// <summary>�e�Z�O�����g�����C���ɓW�J����Ă��邩�̂悤�ɁA�W�I���g���̒������v�Z���܂��B</summary>
        /// <param name="inputGeometryTransform">���̗̈���v�Z����O�ɂ��̃W�I���g���ɓK�p�����ϊ��B</param>
        /// <return>�W�I���g���̒����B</return>
        float ComputeLength(Matrix inputGeometryTransform)
        {
            float length;
            D2D1_MATRIX_3X2_F matrix = inputGeometryTransform.Convert();
            HRESULT hr = this->GetGeometry()->ComputeLength(matrix, &length);
            return (SUCCEEDED(hr) ? length : -1);
        }

        /// <summary>�W�I���g�����w�肳�ꂽ�s��ŕϊ�����A����̋��e�͈͂Ńt���b�g�����ꂽ��A���̃W�I���g���ɉ����Ďw�肳�ꂽ�����������ꂽ�ʒu�ɂ���_�Ɛڐ��x�N�g�����v�Z���܂��B</summary>
        /// <param name="length">���o�����_�Ɛڐ��܂ł̃W�I���g���ɉ����������B</param>
        /// <param name="worldTransform">�w�肳�ꂽ�_�Ɛڐ����v�Z����O�ɃW�I���g���ɓK�p����ϊ��B</param>
        /// <return>�_�Ɛڐ��x�N�g���B</return>
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

        /// <summary>�W�I���g�����w�肳�ꂽ�s��ŕϊ�����A����̋��e�͈͂Ńt���b�g�����ꂽ��A���̃W�I���g���ɉ����Ďw�肳�ꂽ�����������ꂽ�ʒu�ɂ���_�Ɛڐ��x�N�g�����v�Z���܂��B</summary>
        /// <param name="length">���o�����_�Ɛڐ��܂ł̃W�I���g���ɉ����������B</param>
        /// <return>�_�Ɛڐ��x�N�g���B</return>
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
