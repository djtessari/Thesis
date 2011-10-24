/////////////////////
// Animation stuff //
/////////////////////
template <class Vector>
void ParameterSamples<Vector>::setCurrentValue(double t,int type){
	switch (type){
		case LINEAR:
			currentValue=samples[0];
			break;
		case CATMULL_ROM:
			currentValue=samples[0];
			break;
		case UNIFORM_CUBIC_B_SPLINE:
			currentValue=samples[0];
			break;
	};
}
