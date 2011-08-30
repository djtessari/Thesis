using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;

namespace Thesis
{
    public static class CollisionMain
    {
        public static int RectangleCD(Rectangle o1, Rectangle o2)
        {
            int top = Math.Max(o1.Top, o2.Top);
            int bottom = Math.Min(o1.Bottom, o2.Bottom);
            int left = Math.Max(o1.Left, o2.Left);
            int right = Math.Min(o1.Right, o2.Right);

            if (top >= bottom || left >= right)
            {
                return 0;  //no collission
            }
            else if (right - left > bottom - top)
            {
                return 1;  //LR Routine
            }
            else return 2; //UD Routine
        }

/*        public static bool PixelCD(Rectangle o1, Rectangle o2, Texture2D t1, Texture2D t2)
        {
            if (!RectangleCD(o1, o2))
            {
                return false;
            }
            Color[] TextureData1 = new Color[t1.Width * t1.Height];
            t1.GetData(TextureData1);

            Color[] TextureData2 = new Color[t2.Width * t2.Height];
            t2.GetData(TextureData2);

            int top = Math.Max(o1.Top, o2.Top);
            int bottom = Math.Min(o1.Bottom, o2.Bottom);
            int left = Math.Max(o1.Left, o2.Left);
            int right = Math.Min(o1.Right, o2.Right);

            for (int y = top; y < bottom; y++)
                for (int x = left; x < right; x++)
                {
                    Color colorA = TextureData1[(x - o1.Left) + (y - o1.Top) * o1.Width];
                    Color colorB = TextureData2[(x - o2.Left) + (y - o2.Top) * o2.Width];
                    if (colorA.A != 0 && colorB.A != 0) return true;
                }

            return true;
        }*/
    }
}
