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
            // フォント設定
            var format = this.Resources.CreateTextFormat("text format");
            format.FontFamilyName = "Verdana";
            format.FontWeight = DWriteFontWeight.DWRITE_FONT_WEIGHT_REGULAR;
            format.FontStyle = DWriteFontStyle.DWRITE_FONT_STYLE_NORMAL;
            format.FontSize = 12.0f;

            // 円のジオメトリ
            var ellipseGeometry1 = this.Resources.CreateEllipseGeometry("EllipseGeometry1", new PointF(105, 105), 25, 25);
            var ellipseGeometry2 = this.Resources.CreateEllipseGeometry("EllipseGeometry2", new PointF(105, 105), 50, 50);
            var ellipseGeometry3 = this.Resources.CreateEllipseGeometry("EllipseGeometry3", new PointF(105, 105), 75, 75);
            var ellipseGeometry4 = this.Resources.CreateEllipseGeometry("EllipseGeometry4", new PointF(105, 105), 100, 100);

            this.Resources.CreateGeometryGroup(
                "GeoGroup_AlternateFill",
                FillMode.FILL_MODE_ALTERNATE,
                new VisualResourceOfGeometry[] {
                    ellipseGeometry1,
                    ellipseGeometry2,
                    ellipseGeometry3,
                    ellipseGeometry4
                });

            this.Resources.CreateGeometryGroup(
                "GeoGroup_WindingFill",
                FillMode.FILL_MODE_WINDING,
                new VisualResourceOfGeometry[] {
                    ellipseGeometry1,
                    ellipseGeometry2,
                    ellipseGeometry3,
                    ellipseGeometry4
                });


            this.Resources.CreateSolidColorBrush("StrokeBrush", Color.FromArgb(255, 16, 63, 158));
            this.Resources.CreateSolidColorBrush("FillBrush", Color.FromArgb(255, 214, 223, 158));

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

            // テキストを中央揃え
            var textFormat = (VisualResourceOfTextFormat)e.Resources["text format"];
            textFormat.SetTextAlignment(DWriteTextAligment.DWRITE_TEXT_ALIGNMENT_CENTER);

            //
            e.RenderTarget.FillGeometry(e.Resources["GeoGroup_AlternateFill"], e.Resources["FillBrush"]);
            e.RenderTarget.DrawGeometry(e.Resources["GeoGroup_AlternateFill"], e.Resources["StrokeBrush"], 1);
            e.RenderTarget.DrawText("D2D1_FILL_MODE_ALTERNATE",
                                    textFormat,
                                    new RectangleF(5, 215, 205, 240),
                                    e.Resources["StrokeBrush"]);
            //
            e.RenderTarget.SetTransform(300, 0);

            //
            e.RenderTarget.FillGeometry(e.Resources["GeoGroup_WindingFill"], e.Resources["FillBrush"]);
            e.RenderTarget.DrawGeometry(e.Resources["GeoGroup_WindingFill"], e.Resources["StrokeBrush"], 1);
            e.RenderTarget.DrawText("D2D1_FILL_MODE_ALTERNATE",
                                    textFormat,
                                    new RectangleF(5, 215, 205, 240),
                                    e.Resources["StrokeBrush"]);
        }
    }
}
