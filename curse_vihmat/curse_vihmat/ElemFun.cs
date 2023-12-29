using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MathUniver
{
    public class ElemFun
    {
        private double _koef;

        public double Koef
        {
            get { return _koef; }
        }

        private double _degreeX;
        private double _degreeY;

        public ElemFun(double koef, double degreeX, double degreeY)
        {
            _koef = koef;
            _degreeX = degreeX;
            _degreeY = degreeY;
        }

        public double SubstitutionTermsXY(double x, double y)
        {
            return _koef * Math.Pow(x, _degreeX) * Math.Pow(y, _degreeY);
        }

        public void SubstitutionTermX(double x)
        {
            _koef *= Math.Pow(x, _degreeX);
            _degreeX = 0;
        }
        public void SubstitutionTermY(double y)
        {
            _koef *= Math.Pow(y, _degreeY);
            _degreeY = 0;
        }

        public ElemFun DerivativeX()
        {
            ElemFun derivate = new ElemFun(_koef, _degreeX, _degreeY);

            if (derivate._degreeX == 0)
            {
                derivate._koef = 0;

                return derivate;
            }

            derivate._koef *= derivate._degreeX;
            derivate._degreeX -= 1;

            return derivate;
        }

        public ElemFun DerivativeY()
        {
            ElemFun derivate = new ElemFun(_koef, _degreeX, _degreeY);

            if (derivate._degreeY == 0)
            {
                derivate._koef = 0;

                return derivate;
            }

            derivate._koef *= _degreeY;
            derivate._degreeY -= 1;

            return derivate;
        }
    }
}
