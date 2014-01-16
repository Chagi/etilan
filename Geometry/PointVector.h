/* 
 * File:   PointVector.h
 * Author: Elias Forsberg
 *
 * Created on December 26, 2012, 4:19 PM
 * 
 * This class is hoped to be useful for representing N-dimensional points and 
 * vectors. It includes several arithmetic operations that are common for vectors.
 */

#ifndef POINTVECTOR_H
#define	POINTVECTOR_H

#include <array>
#include <ostream>
#include <functional>
#include <initializer_list>

/*
 * Dim is the dimension of the PointVector, and Numberic is the type used to represent
 * the composants. Numeric should overload all arithmetic and comparison operators, 
 * as well as = . It should also have a default constructor.
 */

template<int Dim = 3, typename Numeric = double>
class PointVector{
public:
    
    
public:
	PointVector();
	PointVector(Numeric composants[Dim]);
	
	template<int D2>
	PointVector(PointVector<D2> orig);
	
	PointVector(std::initializer_list<Numeric> list);

private:
	/*
	 *  Constructor helper functions (for the variadic template constructor)
	 */
	template<typename First, typename... Tail>
	inline void pconstruct(int i, First f, Tail... t);
	inline void pconstruct(int i);
    
private:
	Numeric comp[Dim];
	class Cross_product;
    
public:
	/*
	 * Returns composants of the PointVector<Dim>. 
	 * x,y and z represent comp[0], comp[1] and comp[2], respectively. 
	 */
	Numeric get(int i) const;
	Numeric getdx() const;
	Numeric getdy() const;
	Numeric getdz() const;
	
	Numeric& operator[](int i) const;
	Numeric getMagnitude() const;
	Numeric sum_comp() const;
	
	void set(int i, Numeric d);
	void setdx(Numeric d);
	void setdy(Numeric d);
	void setdz(Numeric d);
	
	/*
	 * Some common arithmetic operations. There exist several versions of many
	 * of these operations; as operators, member methods, and static methods.
	 */
	
	inline PointVector operator +(const PointVector r) const;
	inline PointVector operator -(const PointVector r) const;
	inline PointVector operator -() const;
	
	inline PointVector& operator+=(const PointVector r);
	inline PointVector& operator-=(const PointVector r);
	inline PointVector& operator*=(const Numeric r);
	inline PointVector& operator/=(const Numeric r);
	
	template<int D, typename Num>
	friend PointVector<D, Num> operator *(const PointVector<D, Num> l, const Num r);
	template<int D, typename Num>
	friend PointVector<D, Num> operator *(const Num l, const PointVector<D, Num> r);
	template<int D, typename Num>
	friend PointVector<D, Num> operator /(const PointVector<D, Num> l, const Num r);
	template<int D, typename Num>
	friend PointVector<D, Num> operator /(const Num l, const PointVector<D, Num> r);
	
	PointVector& add(PointVector p);
	PointVector& sub(PointVector p);
	static PointVector add(PointVector p, PointVector q);
	static PointVector sub(PointVector p, PointVector q);
	
	PointVector& mul_comp(PointVector p);
	PointVector& mul_cross(PointVector p);
	PointVector& mul(Numeric d);
	static Numeric mul_dot(PointVector p, PointVector q);
	static PointVector mul_comp(PointVector p, PointVector q);
	static PointVector mul_cross(PointVector p, PointVector q);
	static PointVector mul(Numeric d, PointVector p);
	
	PointVector& div_comp(PointVector p);
	PointVector& div(Numeric d);
	static PointVector div_comp(PointVector p, PointVector q);
	static PointVector div(Numeric d, PointVector p);
	
	PointVector& pow(Numeric d);
	PointVector& pow_comp(PointVector p);
	static PointVector pow(Numeric d, PointVector p);
	static PointVector pow_comp(PointVector p, PointVector q);
	
	/*
	 * a is considered max_comp(b) if all components of a are equal to or bigger
	 * than their respective component in b
	 */
	
	PointVector& set_min_comp(PointVector p);
	PointVector& set_max_comp(PointVector p);
	static PointVector min_comp(PointVector p, PointVector q);
	static PointVector max_comp(PointVector p, PointVector q);
	
	bool is_min_comp(PointVector p) const;
	bool is_max_comp(PointVector p) const;
	bool is_eq_comp (PointVector p) const;
	
	/*
	 * A unit vector is a vector with the magnitude 1. make_unit() and 
	 * make_unit(p) scale down their vectors so that their magnitude is one,
	 * but the relative sizes of the composants remain.
	 */
	PointVector& make_unit();
	static PointVector make_unit(PointVector p);
	
	/*
	 * reflect creates a PointVector that is a reflection on the surface of which
	 * normal is the normal vector. Projecting a PointVector p onto q creates a 
	 * PointVector that is the component of p in the direction of q.
	 */
	PointVector& reflect(PointVector normal);
	PointVector& project(PointVector p);
	static PointVector reflect(PointVector p, PointVector normal);
	static PointVector project(PointVector p, PointVector q);
	static Numeric taxicab_distance(PointVector p, PointVector q);
	
	/*
	 * Gerneral composant-wise unary and binary operator for user-defined operations.
	 */
	
	PointVector& op_comp(std::function<Numeric(Numeric)> op);
	PointVector& op_comp(std::function<Numeric(Numeric, Numeric)> op, PointVector p);
	
	std::array<bool, Dim> operator==	(PointVector p) const;
	std::array<bool, Dim> operator!=	(PointVector p) const;
	std::array<bool, Dim> operator> 	(PointVector p) const;
	std::array<bool, Dim> operator< 	(PointVector p) const;
	std::array<bool, Dim> operator>=	(PointVector p) const;
	std::array<bool, Dim> operator<=	(PointVector p) const;
	
	/*
	 * operator<< for ostream to be able to print PointVectors easily. This
	 * requires that Numeric overloads operator << 
	 */
	
	template<int D, typename N>
	friend std::ostream& operator << (std::ostream& out, PointVector<D,N> d);
	
	/*
	 * Cross_product is a class that handles computation of cross products by using 
	 * automatic type casting to the expected return type. This method is used because
	 * of the lack of partial specialization of template class methods.
	 */
	
private:
	class Cross_product{
	public:
		Cross_product(PointVector t, PointVector u);
		
		operator PointVector<3,Numeric> () const;
		operator PointVector<7,Numeric> () const;
	
	private:
		PointVector q, p;
	};
	
};

namespace Boolarr{
	template<int Dim>
	bool all(std::array<bool, Dim> a);
	template<int Dim>
	bool any(std::array<bool, Dim> a);
	template<int Dim>
	bool most(std::array<bool, Dim> a);
}

namespace Geometry{
	template<int Dimension, typename Numeral>
	using Vector = PointVector<Dimension, Numeral>;
}

#endif	/* POINTVECTOR_H */

#include "PointVector.hpp"
