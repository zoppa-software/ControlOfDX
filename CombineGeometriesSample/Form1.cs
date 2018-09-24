using System;
using System.Drawing;
using ControlOfDX;

namespace DrawRectangleExample
{
    public partial class Form1
        : ControlOfDX.VisualForm
    {
        public Form1()
        {
            InitializeComponent();
        }

        protected override void OnInitializeResource(EventArgs e)
        {
            var ellipseGeometry = this.Resources.CreateEllipseGeometry("ellipseGeometry", new PointF(100, 60), 100, 50);

            var pathGeometry = this.Resources.CreatePathGeometry("pathGeometry");
            using (var sink = pathGeometry.CreateGeometrySink()) {
                sink.BeginFigure(new PointF(10, 50), FigureBegin.FIGURE_BEGIN_FILLED);
                sink.AddBezier(new PointF(100, 0), new PointF(200, 200), new PointF(300, 100));
                sink.AddLine(400, 100);
                sink.AddArc(new PointF(200, 100), new SizeF(50, 50), 30, SweepDirection.SWEEP_DIRECTION_COUNTER_CLOCKWISE, ArcSize.ARC_SIZE_LARGE);
                sink.AddBezier(new PointF(150, 50), new PointF(100, 150), new PointF(0, 0));
                sink.EndFigure(FigureEnd.FIGURE_END_OPEN);

                sink.BeginFigure(new PointF(10, 300), FigureBegin.FIGURE_BEGIN_FILLED);
                sink.AddBezier(new PointF(100, 250), new PointF(200, 450), new PointF(300, 350));
                sink.AddLine(400, 350);
                sink.AddArc(new PointF(200, 350), new SizeF(50, 50), 30, SweepDirection.SWEEP_DIRECTION_COUNTER_CLOCKWISE, ArcSize.ARC_SIZE_LARGE);
                sink.AddBezier(new PointF(150, 300), new PointF(100, 400), new PointF(0, 250));
                sink.EndFigure(FigureEnd.FIGURE_END_CLOSED);
            }

            var pathGeometry1 = this.Resources.CreatePathGeometry("pathGeometry1");
            using (var sink = pathGeometry1.CreateGeometrySink()) {
                sink.BeginFigure(new PointF(0, 0), FigureBegin.FIGURE_BEGIN_FILLED);
                sink.AddLines(new PointF[] {
                    new PointF(200, 0),
                    new PointF(300, 200),
                    new PointF(100, 200),
                });
                sink.EndFigure(FigureEnd.FIGURE_END_CLOSED);
            }

            // 黒ブラシ
            this.Resources.CreateSolidColorBrush("brush", Color.Black);

            using (var bmp = new Bitmap(10, 10)) {
                using (var brh = new SolidBrush(Color.FromArgb(255, 237, 239, 245))) {
                    using (var g = Graphics.FromImage(bmp)) {
                        g.Clear(Color.White);
                        g.FillRectangle(brh, 0, 0, 10, 1);
                        g.FillRectangle(brh, 0, 0, 1, 10);
                    }
                    this.Resources.CreateBitmapBrush("GridPatternBitmapBrush", bmp);
                }
            }
        }

        protected override void OnRendering(VisualRenderEventArgs e)
        {
            e.RenderTarget.SetTransform();
            e.RenderTarget.Clear(Color.White);
            e.RenderTarget.FillRectangle(new RectangleF(0, 0, this.Width, this.Height), e.Resources["GridPatternBitmapBrush"]);

            e.RenderTarget.SetTransform(10, 10);
            e.RenderTarget.DrawGeometry(e.Resources["pathGeometry"], e.Resources["brush"], 5);

            e.RenderTarget.SetTransform(500, 65);
            e.RenderTarget.DrawEllipse(new Ellipse(new PointF(100, 60), 100, 50), e.Resources["brush"], 5);

            e.RenderTarget.SetTransform(500, 5);
            e.RenderTarget.DrawGeometry(e.Resources["ellipseGeometry"], e.Resources["brush"], 5);

            e.RenderTarget.SetTransform(500, 200);
            e.RenderTarget.DrawGeometry(e.Resources["pathGeometry1"], e.Resources["brush"], 5);
        }
    }
}
