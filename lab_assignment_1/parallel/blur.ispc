
export inline void blur(uniform int colorR[], uniform int colorR_mod[],uniform int colorG[], uniform int colorG_mod[],uniform int colorB[], uniform int colorB_mod[], uniform int width, uniform int height)
{
	foreach (c = 1 ... width - 1, r = 0 ... height - 1){
		colorR_mod[(c * height) + r] = (colorR[((c-1) * height) + (r-1)] / 8) +  (colorR[((c-1) * height) + r] / 8) + (colorR[((c-1) * height) + (r+1)] / 8) + (colorR[(c * height) + (r-1)] / 8) + (colorR[(c * height) + (r+1)] / 8) + (colorR[((c+1) * height) + (r-1)] / 8) + (colorR[((c+1) * height) + r] / 8) + (colorR[((c+1) * height) + (r+1)] / 8);	
		colorG_mod[(c * height) + r] = (colorG[((c-1) * height) + (r-1)] / 8) +  (colorG[((c-1) * height) + r] / 8) + (colorG[((c-1) * height) + (r+1)] / 8) + (colorG[(c * height) + (r-1)] / 8) + (colorG[(c * height) + (r+1)] / 8) + (colorG[((c+1) * height) + (r-1)] / 8) + (colorG[((c+1) * height) + r] / 8) + (colorG[((c+1) * height) + (r+1)] / 8);	
		colorB_mod[(c * height) + r] = (colorB[((c-1) * height) + (r-1)] / 8) +  (colorB[((c-1) * height) + r] / 8) + (colorB[((c-1) * height) + (r+1)] / 8) + (colorB[(c * height) + (r-1)] / 8) + (colorB[(c * height) + (r+1)] / 8) + (colorB[((c+1) * height) + (r-1)] / 8) + (colorB[((c+1) * height) + r] / 8) + (colorB[((c+1) * height) + (r+1)] / 8);	
	}
}
