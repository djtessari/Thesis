/////////////////////
// Animation stuff //
/////////////////////
template <class Vector>
void ParameterSamples<Vector>::setCurrentValue(double t,int type){
	double dt,tt,t2,t3,ddt;
	double c0,c1,c2,c3;
	int idx,idx0,idx3;
	switch (type){
		case LINEAR:
			tt=t*(count-1);
			idx=(int)tt;
			dt=tt-idx;
			if(t<=0){currentValue=samples[0];}
			else if(t>=1){currentValue=samples[count-1];}
			else{currentValue=samples[idx]*(1-dt)+samples[idx+1]*dt;}
//			currentValue=samples[0];
			break;
		case CATMULL_ROM:
			tt=t*(count-1);
			idx=(int)tt;
			dt=tt-idx;
			if(t<=0){currentValue=samples[0];}
			else if(t>=1){currentValue=samples[count-1];}
			else{
				if(idx==0){idx0=idx;}
				else{idx0=idx-1;}
				if(idx==count-2){idx3=count-1;}
				else{idx3=idx+2;}
				t2=dt*dt;
				t3=dt*t2;
				c0=-t3/2+t2-dt/2;
				c1=(1.5)*t3+(-2.5)*t2+1;
				c2=(-1.5)*t3+2*t2+dt/2;
				c3=(t3-t2)/2;
				currentValue=samples[idx0]*c0+samples[idx]*c1+samples[idx+1]*c2+samples[idx3]*c3;
			}
//			currentValue=samples[0];
			break;
		case UNIFORM_CUBIC_B_SPLINE:
			tt=t*(count-1);
			idx=(int)tt;
			dt=tt-idx;
			ddt=1-dt;
			if(t<=0){currentValue=samples[0];}
			else if(t>=1){currentValue=samples[count-1];}
			else{
				if(idx==0){idx0=idx;}
				else{idx0=idx-1;}
				if(idx==count-2){idx3=count-1;}
				else{idx3=idx+2;}
				t2=dt*dt;
				t3=dt*t2;
				c0=ddt*ddt*ddt/6;
				c1=(3*t3-6*t2+4)/6;
				c2=(-3*t3+3*t2+3*dt+1)/6;
				c3=t3/6;
				currentValue=samples[idx0]*c0+samples[idx]*c1+samples[idx+1]*c2+samples[idx3]*c3;
			}
//			currentValue=samples[0];
			break;
	};
}
