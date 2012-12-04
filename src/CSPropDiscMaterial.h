/*
*	Copyright (C) 2008-2012 Thorsten Liebig (Thorsten.Liebig@gmx.de)
*
*	This program is free software: you can redistribute it and/or modify
*	it under the terms of the GNU Lesser General Public License as published
*	by the Free Software Foundation, either version 3 of the License, or
*	(at your option) any later version.
*
*	This program is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*	GNU Lesser General Public License for more details.
*
*	You should have received a copy of the GNU Lesser General Public License
*	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "CSProperties.h"
#include "CSPropMaterial.h"

//! Continuous Structure Discrete Material Property
/*!
  This Property reads a discrete material distribution from a file. (currently only HDF5)
  */
class CSXCAD_EXPORT CSPropDiscMaterial : public CSPropMaterial
{
public:
	CSPropDiscMaterial(ParameterSet* paraSet);
	CSPropDiscMaterial(CSProperties* prop);
	CSPropDiscMaterial(unsigned int ID, ParameterSet* paraSet);
	virtual ~CSPropDiscMaterial();

	virtual const string GetTypeXMLString() const {return string("Discrete-Material");}

	virtual double GetEpsilonWeighted(int ny, const double* coords);
	virtual double GetMueWeighted(int ny, const double* coords);
	virtual double GetKappaWeighted(int ny, const double* coords);
	virtual double GetSigmaWeighted(int ny, const double* coords);

	virtual double GetDensityWeighted(const double* coords);

	virtual void Init();

	virtual bool Write2XML(TiXmlNode& root, bool parameterised=true, bool sparse=false);
	virtual bool ReadFromXML(TiXmlNode &root);

	bool ReadHDF5(string filename);

protected:
	unsigned int GetWeightingPos(const double* coords);

	int m_FileType;
	string m_Filename;
	unsigned int m_Size[3];
	float *m_mesh[3];
	float *m_Disc_epsR;
	float *m_Disc_kappa;
	float *m_Disc_mueR;
	float *m_Disc_sigma;
	float *m_Disc_Density;
	double m_Scale;
	CSTransform* m_Transform;

	float* ReadDataSet(string filename, string d_name, int &rank, unsigned int &size, bool debug=false);
};
