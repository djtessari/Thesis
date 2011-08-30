// *****************************************************************************
// http://www.progware.org/blog/ - Collision Detection Algorithms
// *****************************************************************************

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;

namespace XNA2DCollisionDetection
{
    public enum UseForCollisionDetection { Triangles, Rectangles, Circles,PerPixel }

    public static class CollisionDetection2D
    {
        public static UseForCollisionDetection CDPerformedWith { get; set; }

        public static bool BoundingRectangle(int x1,int y1,int width1,int height1,int x2,int y2,int width2,int height2)
        {
            Rectangle rectangleA = new Rectangle((int)x1, (int)y1, width1, height1);
            Rectangle rectangleB = new Rectangle((int)x2, (int)y2, width2, height2);

            int top = Math.Max(rectangleA.Top, rectangleB.Top);
            int bottom = Math.Min(rectangleA.Bottom, rectangleB.Bottom);
            int left = Math.Max(rectangleA.Left, rectangleB.Left);
            int right = Math.Min(rectangleA.Right, rectangleB.Right);

            if (top >= bottom || left >= right)
                return false;

            return true;
        }
        public static bool BoundingCircle(int x1, int y1, int radius1, int x2, int y2, int radius2)
        {
            Vector2 V1 = new Vector2(x1, y1);
            Vector2 V2 = new Vector2(x2, y2);

            Vector2 Distance = V1 - V2;

            if (Distance.Length() < radius1 + radius2)
                return true;

            return false;
        }
        public static bool BoundingTriangles(List<Vector2> p1, List<Vector2> p2)
        {
            for (int i = 0; i < 3; i++)
                if (_isPointInsideTriangle(p1, p2[i])) return true;

            for (int i = 0; i < 3; i++)
                if (_isPointInsideTriangle(p2, p1[i])) return true;
            return false;
        }
        private static bool _isPointInsideTriangle(List<Vector2> TrianglePoints, Vector2 p)
        {
            // Translated to C# from: http://www.ddj.com/184404201
            Vector2 e0 = p - TrianglePoints[0];
            Vector2 e1 = TrianglePoints[1] - TrianglePoints[0];
            Vector2 e2 = TrianglePoints[2] - TrianglePoints[0];

            float u, v = 0;
            if (e1.X == 0)
            {
                if (e2.X == 0) return false;
                u = e0.X / e2.X;
                if (u < 0 || u > 1) return false;
                if (e1.Y == 0) return false;
                v = (e0.Y - e2.Y * u) / e1.Y;
                if (v < 0) return false;
            }
            else
            {
                float d = e2.Y * e1.X - e2.X * e1.Y;
                if (d == 0) return false;
                u = (e0.Y * e1.X - e0.X * e1.Y) / d;
                if (u < 0 || u > 1) return false;
                v = (e0.X - e2.X * u) / e1.X;
                if (v < 0) return false;
                if ((u + v) > 1) return false;
            }

            return true;
        }
        public static bool PerPixel(Texture2D Texture1, Texture2D Texture2, Vector2 Pos1, Vector2 Pos2)
        {
            Rectangle Rectangle1 = new Rectangle((int)Pos1.X, (int)Pos1.Y, Texture1.Width, Texture1.Height);
            Rectangle Rectangle2 = new Rectangle((int)Pos2.X, (int)Pos2.Y, Texture2.Width, Texture2.Height);

            if (!BoundingRectangle(Rectangle1.X, Rectangle1.Y, Rectangle1.Width, Rectangle1.Height,
                                  Rectangle2.X, Rectangle2.Y, Rectangle2.Width, Rectangle2.Height))
                return false;

            // Bounding rectangles collide beyond this point so we need to check
            // a per-pixel collision

            Color[] TextureData1 = new Color[Texture1.Width * Texture1.Height];
            Texture1.GetData(TextureData1);

            Color[] TextureData2 = new Color[Texture2.Width * Texture2.Height];
            Texture2.GetData(TextureData2);

            int top = Math.Max(Rectangle1.Top, Rectangle2.Top);
            int bottom = Math.Min(Rectangle1.Bottom, Rectangle2.Bottom);
            int left = Math.Max(Rectangle1.Left, Rectangle2.Left);
            int right = Math.Min(Rectangle1.Right, Rectangle2.Right);

            for (int y = top; y < bottom; y++)
                for (int x = left; x < right; x++)
                {
                    Color colorA = TextureData1[(x - Rectangle1.Left) + (y - Rectangle1.Top) * Rectangle1.Width];
                    Color colorB = TextureData2[(x - Rectangle2.Left) + (y - Rectangle2.Top) * Rectangle2.Width];
                    if (colorA.A != 0 && colorB.A != 0) return true;
                }
            return false;
        }
    }
}
