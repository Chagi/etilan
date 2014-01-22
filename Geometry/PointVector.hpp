/* 
 * File:   PointVector.cpp
 * Author: Elias Forsberg
 *
 * Created on December 26, 2012, 4:20 PM
 */

#ifndef POINTVECTOR_CPP
#define POINTVECTOR_CPP

#include "PointVector.h"
#include <math.h>
#include <cassert>
#include <stdexcept>

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>::PointVector():
	comp {}
{}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>::PointVector(Numeric composants[Dim]){
	std::copy(composants, composants+Dim, comp);
}

template<int Dim, typename Numeric>
template<int D2>
PointVector<Dim, Numeric>::PointVector(PointVector<D2> orig):
	comp {}
{
	constexpr int m = std::min(Dim, D2);
	std::copy(orig.comp, orig.comp + m, comp);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>::PointVector(std::initializer_list<Numeric> list){
	int i = 0;
	for(Numeric n : list){
		comp[i] = n;
		i++;
	}
}

template<int Dim, typename Numeric>
template<typename First, typename... Tail>
inline void PointVector<Dim, Numeric>::pconstruct(int i, First f, Tail... t){
	comp[i] = f;
	pconstruct(i+1, t...);
}

template<int Dim, typename Numeric>
inline void PointVector<Dim, Numeric>::pconstruct(int /*i*/){}

template<int Dim, typename Numeric>
Numeric PointVector<Dim, Numeric>::get(int i) const{
	assert(i <= Dim);
	return comp[i];
}

template<int Dim, typename Numeric>
Numeric PointVector<Dim, Numeric>::getdx() const{
	static_assert(Dim >= 1, "This PointVector does not have an x-component");
    return comp[0];
}

template<int Dim, typename Numeric>
Numeric PointVector<Dim, Numeric>::getdy() const{
    static_assert(Dim >= 2, "This PointVector does not have a y-component");
    return comp[1];
}

template<int Dim, typename Numeric>
Numeric PointVector<Dim, Numeric>::getdz() const{
    static_assert(Dim >= 3, "This PointVector does not have a z-component");
    return comp[2];
}

template<int Dim, typename Numeric>
Numeric PointVector<Dim, Numeric>::getMagnitude() const{
	Numeric mag = 0;
	for(int i = 0; i < Dim; i++){
		mag += comp[i] * comp[i];
	}
	return sqrt(mag);
}

template<int Dim, typename Numeric>
Numeric PointVector<Dim, Numeric>::sum_comp() const{
	Numeric sum = 0;
	for(auto x : comp){
		sum += x;
	}
	return sum;
}

template<int Dim, typename Numeric>
Numeric& PointVector<Dim, Numeric>::operator[](int i) {
	return comp[i];
}

template<int Dim, typename Numeric>
void PointVector<Dim, Numeric>::set(int i, Numeric d){
	assert(i <= Dim);
	comp[i] = d;
}

template<int Dim, typename Numeric>
void PointVector<Dim, Numeric>::setdx(Numeric d){
	static_assert(Dim >= 1, "This PointVector does not have an x-component");
	comp[0] = d;
}

template<int Dim, typename Numeric>
void PointVector<Dim, Numeric>::setdy(Numeric d){
	static_assert(Dim >= 2, "This PointVector does not have a y-component");
	comp[1] = d;
}

template<int Dim, typename Numeric>
void PointVector<Dim, Numeric>::setdz(Numeric d){
	static_assert(Dim >= 3, "This PointVector does not have a z-component");
	comp[2] = d;
}

template<int Dim, typename Numeric>
inline PointVector<Dim, Numeric> PointVector<Dim, Numeric>::operator +(const PointVector<Dim, Numeric> r) const{
	return PointVector<Dim, Numeric>::add(*this, r);
}

template<int Dim, typename Numeric>
inline PointVector<Dim, Numeric> PointVector<Dim, Numeric>::operator -(const PointVector<Dim, Numeric> r) const{
	return PointVector<Dim, Numeric>::sub(*this, r);
}

template<int Dim, typename Numeric>
inline PointVector<Dim, Numeric> PointVector<Dim, Numeric>::operator -() const{
	return PointVector<Dim, Numeric>::mul(-1, *this);
}

template<int Dim, typename Numeric>
inline PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::operator +=(const PointVector<Dim, Numeric> r){
	this->add(r);
	return *this;
}

template<int Dim, typename Numeric>
inline PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::operator -=(const PointVector<Dim, Numeric> r){
	this->sub(r);
	return *this;
}

template<int Dim, typename Numeric>
inline PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::operator *=(const Numeric r){
	this->mul(r);
	return *this;
}

template<int Dim, typename Numeric>
inline PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::operator /=(const Numeric r){
	this->div(r);
	return *this;
}

template<int D, typename Num>
inline PointVector<D, Num> operator*(const PointVector<D, Num> l, const Num r){
	return PointVector<D, Num>::mul(r, l);
}

template<int D, typename Num>
inline PointVector<D, Num> operator*(const Num l, const PointVector<D, Num> r){
	return PointVector<D, Num>::mul(l, r);
}

template<int D, typename Num>
inline PointVector<D, Num> operator/(const PointVector<D, Num> l, const Num r){
	return PointVector<D, Num>::div(r, l);
}

template<int D, typename Num>
inline PointVector<D, Num> operator/(const Num l, const PointVector<D, Num> r){
	PointVector<D, Num> a;
	for(int i = 0; i < D; i++){
		a.comp[i] = 1.0/r.comp [i];
	}
	return PointVector<D, Num>::mul_comp(a, l);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::add(PointVector<Dim, Numeric> p){
	for(int i = 0; i < Dim; i++){
		comp[i] += p.comp[i];
	}
	return *this;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::sub(PointVector<Dim, Numeric> p){
	for(int i = 0; i < Dim; i++){
		comp[i] -= p.comp[i];
	}
	return *this;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::add(PointVector<Dim, Numeric> p, PointVector<Dim, Numeric> q){
	return p.add(q);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::sub(PointVector<Dim, Numeric> p, PointVector<Dim, Numeric> q){
	return p.sub(q);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::mul_comp(PointVector<Dim, Numeric> p){
	for(int i = 0; i < Dim; i++){
		comp[i] *= p.comp[i];
	}
	return *this;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::mul_cross(PointVector<Dim, Numeric> p){
	return Cross_product(*this, p);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::mul(Numeric d){
	for(int i = 0; i < Dim; i++){
		comp[i] *= d;
	}
	return *this;
}

template<int Dim, typename Numeric>
Numeric PointVector<Dim, Numeric>::mul_dot(PointVector<Dim, Numeric> p, PointVector<Dim, Numeric> q){
	Numeric result = 0;
	for(int i = 0; i < Dim; i++){
		result += p.comp[i] * q.comp[i];
	}
	return result;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::mul_comp(PointVector<Dim, Numeric> p, PointVector<Dim, Numeric> q){
	return p.mul_comp(q);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::mul_cross(PointVector<Dim, Numeric> p, PointVector<Dim, Numeric> q){
	return Cross_product(p,q);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::mul(Numeric d, PointVector<Dim, Numeric> p){
	return p.mul(d);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::div_comp(PointVector<Dim, Numeric> p){
    for(int i = 0; i < Dim; i++){
		comp[i] /= p.comp[i];
	}
	return *this;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::div(Numeric d){
	for(int i = 0; i < Dim; i++){
		comp[i] /= d;
	}
	return *this;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::div_comp(PointVector<Dim, Numeric> p, PointVector<Dim, Numeric> q){
	return p.div_comp(q);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::div(Numeric d, PointVector p){
	return p.div(d);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::pow(Numeric d){
	for(int i = 0; i < Dim; i++){
		comp[i] = pow(comp[i], d);
	}
	return *this;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::pow_comp(PointVector p){
	for(int i = 0; i < Dim; i++){
		comp[i] = pow(comp[i], p.comp[i]);
	}
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::pow(Numeric d, PointVector p){
	return p.pow(d);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::pow_comp(PointVector p, PointVector q){
	return p.pow_comp(q);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::set_min_comp(PointVector<Dim, Numeric> p){
	for(int i = 0; i < Dim; i++){
		*(comp+i) = *(comp+i) < *(p.comp+i) ? *(comp+i) : *(p.comp+i);
	}
	return *this;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::set_max_comp(PointVector<Dim, Numeric> p){
	for(int i = 0; i < Dim; i++){
		*(comp+i) = *(comp+i) > *(p.comp+i) ? *(comp+i) : *(p.comp+i);
	}
	return *this;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::min_comp(PointVector p, PointVector q){
	return p.set_min_comp(q);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::max_comp(PointVector p, PointVector q){
	return p.set_max_comp(q);
}

template<int Dim, typename Numeric>
bool PointVector<Dim, Numeric>::is_min_comp(PointVector<Dim, Numeric> p) const{
	for(int i = 0; i < Dim; i++){
		if(comp[i] > p.comp[i])
			return false;
	}
	return true;
}

template<int Dim, typename Numeric>
bool PointVector<Dim, Numeric>::is_max_comp(PointVector<Dim, Numeric> p) const{
	for(int i = 0; i < Dim; i++){
		if(comp[i] < p.comp[i])
			return false;
	}
	return true;
}

template<int Dim, typename Numeric>
bool PointVector<Dim, Numeric>::is_eq_comp(PointVector<Dim, Numeric> p) const{
	for(int i = 0; i < Dim; i++){
		if(comp[i] != p.comp[i])
			return false;
	}
	return true;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::make_unit(){
	Numeric mag = getMagnitude();
	if(mag==0)
		throw std::length_error("Zero vector has no direction");
	for(int i = 0; i < Dim; i++){
		comp[i] /= mag; 
	}
	return *this;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::make_unit(PointVector<Dim, Numeric> p){
	return p.make_unit();
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::reflect(PointVector<Dim, Numeric> normal){
	PointVector<Dim, Numeric> p = *this;
	normal.make_unit();
	*this = 2.0 * mul_dot(p, normal) * normal - p;
	return *this;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::project(PointVector p){
	PointVector<Dim, Numeric>& res = *this;
	mul_dot(res, p)/mul_dot(p,p) * p;
	return res;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::reflect(PointVector<Dim, Numeric> p, PointVector<Dim, Numeric> normal){
	return p.reflect(normal);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::project(PointVector p, PointVector q){
	return p.project(q);
}

template<int Dim, typename Numeric>
Numeric PointVector<Dim, Numeric>::taxicab_distance(PointVector p, PointVector q){
	Numeric res;
	for(int i = 0; i < Dim; i++){
		res += abs(p.comp[i] - q.comp[i]);
	}
	return res;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::op_comp(std::function<Numeric(Numeric)> op){
	for(Numeric& n : comp){
		n = op(n);
	}
	return *this;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::op_comp(std::function<Numeric(Numeric, Numeric)> op, PointVector<Dim, Numeric> p){
	for(int i = 0; i < Dim; i++){
		comp[i] = op(comp[i], p.comp[i]);
	}
	return *this;
}

template<int Dim, typename Numeric>
std::array<bool, Dim> PointVector<Dim, Numeric>::operator ==(PointVector<Dim, Numeric> p) const{
	std::array<bool, Dim> result;
	for(int i = 0; i < Dim; i++){
		result[i] = comp[i] == p.comp[i];
	}
	return result;
}

template<int Dim, typename Numeric>
std::array<bool, Dim> PointVector<Dim, Numeric>::operator !=(PointVector<Dim, Numeric> p) const{
	std::array<bool, Dim> result;
	for(int i = 0; i < Dim; i++){
		result[i] = comp[i] != p.comp[i];
	}
	return result;
}

template<int Dim, typename Numeric>
std::array<bool, Dim> PointVector<Dim, Numeric>::operator >(PointVector<Dim, Numeric> p) const{
	std::array<bool, Dim> result;
	for(int i = 0; i < Dim; i++){
		result[i] = comp[i] > p.comp[i];
	}
	return result;
}

template<int Dim, typename Numeric>
std::array<bool, Dim> PointVector<Dim, Numeric>::operator <(PointVector<Dim, Numeric> p) const{
	std::array<bool, Dim> result;
	for(int i = 0; i < Dim; i++){
		result[i] = comp[i] < p.comp[i];
	}
	return result;
}

template<int Dim, typename Numeric>
std::array<bool, Dim> PointVector<Dim, Numeric>::operator >=(PointVector<Dim, Numeric> p) const{
	std::array<bool, Dim> result;
	for(int i = 0; i < Dim; i++){
		result[i] = comp[i] >= p.comp[i];
	}
	return result;
}

template<int Dim, typename Numeric>
std::array<bool, Dim> PointVector<Dim, Numeric>::operator <=(PointVector<Dim, Numeric> p) const{
	std::array<bool, Dim> result;
	for(int i = 0; i < Dim; i++){
		result[i] = comp[i] <= p.comp[i];
	}
	return result;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>::Cross_product::Cross_product(PointVector<Dim, Numeric> t, PointVector<Dim, Numeric> u){
	q = t;
	p = u;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>::Cross_product::operator PointVector<3, Numeric> () const{
	PointVector<3, Numeric> res;
	res.comp[0] = q.comp[1] * p.comp[2] - q.comp[2] * p.comp[1];
	res.comp[1] = q.comp[2] * p.comp[0] - q.comp[0] * p.comp[2];
	res.comp[2] = q.comp[0] * p.comp[1] - q.comp[1] * p.comp[0];
	return res;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>::Cross_product::operator PointVector<7, Numeric> () const{
	PointVector<7, Numeric> res;
	res.comp[0] = q.comp[1] * p.comp[3] - q.comp[3] * p.comp[1] + q.comp[2] * p.comp[6] - q.comp[6] * p.comp[2] + q.comp[4] * p.comp[5] - q.comp[5] * p.comp[4];
	res.comp[1] = q.comp[2] * p.comp[4] - q.comp[4] * p.comp[2] + q.comp[3] * p.comp[0] - q.comp[0] * p.comp[3] + q.comp[5] * p.comp[6] - q.comp[6] * p.comp[5];
	res.comp[2] = q.comp[3] * p.comp[5] - q.comp[5] * p.comp[3] + q.comp[4] * p.comp[1] - q.comp[1] * p.comp[4] + q.comp[6] * p.comp[0] - q.comp[0] * p.comp[6];
	res.comp[3] = q.comp[4] * p.comp[6] - q.comp[6] * p.comp[4] + q.comp[5] * p.comp[2] - q.comp[2] * p.comp[5] + q.comp[0] * p.comp[1] - q.comp[1] * p.comp[0];
	res.comp[4] = q.comp[5] * p.comp[0] - q.comp[0] * p.comp[5] + q.comp[6] * p.comp[3] - q.comp[3] * p.comp[6] + q.comp[1] * p.comp[2] - q.comp[2] * p.comp[1];
	res.comp[5] = q.comp[6] * p.comp[1] - q.comp[1] * p.comp[6] + q.comp[0] * p.comp[4] - q.comp[4] * p.comp[0] + q.comp[2] * p.comp[3] - q.comp[3] * p.comp[2];
	res.comp[6] = q.comp[0] * p.comp[2] - q.comp[2] * p.comp[0] + q.comp[1] * p.comp[5] - q.comp[5] * p.comp[1] + q.comp[3] * p.comp[4] - q.comp[4] * p.comp[3];
	return res;
}

template<int Dim, typename Numeric>
std::ostream& operator<<(std::ostream& out, PointVector<Dim, Numeric> d) {
	out << "{";
	for(int i = 0; i < Dim; i++){
		out << d.comp[i];
		if(i < Dim - 1){
			out << ", ";
		}
	}
	out << "}";
	return out;
}

template<int Dim, typename Numeric>
bool Boolarr::all(std::array<bool,Dim> a){
	for(int i = 0; i < Dim; i++){
		if(!a[i]){
			return false;
		}
	}
	return true;
}

template<int Dim, typename Numeric>
bool Boolarr::any(std::array<bool,Dim> a){
	for(int i = 0; i < Dim; i++){
		if(a[i]){
			return true;
		}
	}
	return false;
}

template<int Dim, typename Numeric>
bool Boolarr::most(std::array<bool,Dim> a){
	int temp = 0;
	for(int i = 0; i < Dim; i++){
		if(a[i]){
			temp++;
		}
	}
	return temp >= Dim/2.0;
}

template<int P1, int P2>
void rotate(PointVector<4>& vec, double angle){
	static_assert(P1 < P2, "Invalid rotation");
	PointVector<4, PointVector<4>> rmat{{1,0,0,0},
	                                    {0,1,0,0},
	                                    {0,0,1,0},
	                                    {0,0,0,1}};
	rmat[P1][P1] = cos(angle);
	rmat[P1][P2] = sin(angle);
	rmat[P2][P1] =-sin(angle);
	rmat[P2][P2] = cos(angle);
	PointVector<4, PointVector<4>> result;
	vec[0] = rmat[0].mul_comp(vec).sum_comp();
	vec[1] = rmat[1].mul_comp(vec).sum_comp();
	vec[2] = rmat[2].mul_comp(vec).sum_comp();
	vec[3] = rmat[3].mul_comp(vec).sum_comp();
}

template<>
inline void rotate<2,3>(PointVector<4>& vec, double angle){
	PointVector<4, PointVector<4>> rmat{{1,0,0,0},
	                                    {0,1,0,0},
	                                    {0,0,1,0},
	                                    {0,0,0,1}};
	rmat[2][2] = cos(angle);
	rmat[2][3] =-sin(angle);
	rmat[3][2] = sin(angle);
	rmat[3][3] = cos(angle);
	PointVector<4, PointVector<4>> result;
	vec[0] = rmat[0].mul_comp(vec).sum_comp();
	vec[1] = rmat[1].mul_comp(vec).sum_comp();
	vec[2] = rmat[2].mul_comp(vec).sum_comp();
	vec[3] = rmat[3].mul_comp(vec).sum_comp();
}

/*
inline void rotate(PointVector<4>& v, int p_a, int p_b, double angle){
	PointVector<4, PointVector<4>> rmat{{1,0,0,0},
	                                    {0,1,0,0},
	                                    {0,0,1,0},
	                                    {0,0,0,1}};
	
	vec[0] = rmat[0].mul_comp(vec).sum_comp();
	vec[1] = rmat[1].mul_comp(vec).sum_comp();
	vec[2] = rmat[2].mul_comp(vec).sum_comp();
	vec[3] = rmat[3].mul_comp(vec).sum_comp();
}*/
#endif /*POINTVECTOR_CPP*/
