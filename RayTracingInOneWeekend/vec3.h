#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3 {
public:
	// デフォルトコンストラクタ
	vec3() : e{0,0,0} {}

	// 引数つきコンストラクタ
	vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

	// 各成分にアクセスするためのメンバ関数(vec.x()的なやつ)
	double x() const { return e[0]; }
	double y() const { return e[1]; }
	double z() const { return e[2]; }

	// 単項演算子 '-' のオーバーロード
	vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }

	// 添え字演算子 '[]' のオーバーロード
	double operator[](int i) const { return e[i]; }
	double& operator[](int i) { return e[i]; }
	
	// 複合代入演算子 '+=' のオーバーロード
	vec3& operator += (const vec3 &v) {
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	// 複合代入演算子 '*=' のオーバーロード
	vec3& operator *= (const double t) {
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	// 複合代入演算子 '/=' のオーバーロード
	vec3& operator /= (const double t) {
		return *this *= 1 / t;
	}

	// ベクトルの長さを計算するメンバ関数
	double length() const {
		return sqrt(length_squared());
	}

	// ベクトルの長さの2乗を計算するメンバ関数
	double length_squared() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

public:
	// メンバ変数として3つの要素を持つ配列
	double e[3];
};


// vec3 の型エイリアス(既存の型や値に新しい名前をつける仕組み＝新しい名前のコピー)
//c++11以降ではusingを、以前ではtypedefを用いる。
using point3 = vec3; // 3D点
using color = vec3; // RGB色




// vec3 ユーティリティ関数
// コンパイラに対し、インライン展開を提案する
// インライン展開とは、小さい関数などが頻繁に呼び出される場合、
// 呼び出しのオーバーヘッドが性能に悪影響を与える可能性があるため、
// 関数の本体を呼び出し元のコードに埋め込んでしまう方法。
// 一般にはヘッダーファイルに書かれることが多く、クラスのメンバ関数などが
// 頻繁に呼ばれる場合、inlineを用いることで性能向上が期待できる。

// vec3をstd::coutで出力可能にしている
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

// 以下はvec3の計算を定義
inline vec3 operator+(const vec3& u, const vec3& v) {
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& v) {
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3& v, double t) {
	return t * v;
}

inline vec3 operator/(vec3 v, double t) {
	return (1 / t) * v;
}

// dot(v1, v2)
inline double dot(const vec3& u, const vec3& v) {
	return u.e[0] * v.e[0]
		+ u.e[1] * v.e[1]
		+ u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
	return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[2] * v.e[0] - u.e[0] * v.e[2],
		u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

// 正規化
inline vec3 unit_vector(vec3 v) {
	return v / v.length();
}

#endif