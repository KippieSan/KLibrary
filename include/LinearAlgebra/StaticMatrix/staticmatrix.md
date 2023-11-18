# StaticMatrix

行列データをC配列(`std::array`)に保存する行列クラス

テンプレートパラメータは行列要素の型(`ElemT`)、行数(`Rows`)、列数(`Cols`)である。

## Base

コンストラクタ及び基本的な機能が実装されている。

### コンストラクタ

$\mathrm{Rows}\times \mathrm{Cols}$行列を初期化する。

```cpp
StaticMatrixBase(const ElemT& elem = ElemT());                                          // (1)
StaticMatrixBase(std::initializer_list<std::initializer_list<ElemT>>&& input_matrix);   // (2)
StaticMatrixBase(std::initializer_list<ElemT>&& input_matrix);                          // (3)
StaticMatrixBase(const Array<Array<ElemT, Cols>, Rows>& input_matrix);                  // (4)
StaticMatrixBase(const Array<ElemT, Rows * Cols>& input_matrix);                        // (5)
StaticMatrixBase(const StaticMatrixBase<ElemT, Rows, Cols>& input);                     // (6)
StaticMatrixBase(StaticMatrixBase<ElemT, Rows, Cols>&& input);                          // (7)
```


- (1) 全ての要素を`elem`で初期化する。デフォルトコンストラクタ
- (2) 2次元の`initializer_list`により行列を初期化する
- (3) 1次元の`initializer_list`により行列を初期化する
- (4) 2次元の`std::array`により行列を初期化する
- (5) 1次元の`std::array`により行列を初期化する
- (6) コピーコンストラクタ
- (7) ムーブコンストラクタ

#### 使用例

```cpp
StaticMatrixBase<int, 2, 3> m1;                                                         // (1)
StaticMatrixBase<int, 2, 3> m2{5};                                                      // (1)
StaticMatrixBase<int, 2, 3> m3{{{1, 2, 3}, {2, 3, 4}}};                                 // (2)
StaticMatrixBase<int, 2, 3> m4{{1, 2, 3, 4, 5, 6}};                                     // (3)
std::array<std::array<int, 3>, 2> arr1 = {{1, 2, 3}, {2, 3, 4}};
std::array<int, 6> arr2 = {1, 2, 3, 4, 5, 6};
StaticMatrixBase<int, 2, 3> m5{arr1};                                                   // (4)
StaticMatrixBase<int, 2, 3> m6{arr2};                                                   // (5)
StaticMatrixBase<int, 2, 3> m7{m1};                                                     // (6)
StaticMatrixBase<int, 2, 3> m8{StaticMatrixBase<int, 2, 3>{{1, 2, 3, 4, 5, 6}}};        // (7)
```

### 演算子

演算子は代入演算子、算術演算子、関数呼び出し演算子、出力演算子が定義されている。
以下、テンプレートパラメータは省略するものとする。

#### 代入演算子

```cpp
auto& operator=(const StaticMatrixBase& input);                                         // (1)
auto& operator=(StaticMatrixBase&& input);                                              // (2)
```

- (1) コピー代入
- (2) ムーブ代入

#### 代入算術演算子

行列同士の代入演算は同型でのみ許可される。

```cpp
auto& operator+=(const StaticMatrixBase& matrix);                                       // (1)
auto& operator-=(const StaticMatrixBase& matrix);                                       // (2)
auto& operator*=(const StaticMatrixBase& matrix);                                       // (3)
auto& operator*=(const ScalarType& scalar);                                             // (4)
auto& operator/=(const ScalarType& scalar);                                             // (5)
```

- (1) 行列値の加算代入演算子
- (2) 行列値の減算代入演算子
- (3) 行列値の乗算代入演算子
- (4) スカラー値の乗算代入演算子
- (5) スカラー値の除算代入演算子

#### 単項演算子

```cpp
auto operator+(const StaticMatrixBase& matrix);                                         // (1)
auto operator-(const StaticMatrixBase& matrix);                                         // (2)
```

- (1) `matrix`をそのまま返す
- (2) 全要素に$-1$を掛けて返す。

#### 算術演算子

```cpp
auto operator+(const StaticMatrixBase& lhs, const StaticMatrixBase& rhs);               // (1)
auto operator-(const StaticMatrixBase& lhs, const StaticMatrixBase& rhs);               // (2)
auto operator*(const StaticMatrixBase& lhs, const StaticMatrixBase& rhs);               // (3)
auto operator*(const StaticMatrixBase& lhs, const ScalarType& rhs);                     // (4)
auto operator*(const ScalarType& lhs, const StaticMatrixBase& rhs);                     // (5)
auto operator/(const StaticMatrixBase& lhs, const ScalarType& rhs);                     // (6)
```

- (1) 行列-行列加算
- (2) 行列-行列減算
- (3) 行列-行列乗算
- (4) 行列-スカラー乗算
- (5) スカラー-行列乗算
- (6) 行列-スカラー減算

四則演算は左オペランドの要素の型(`ElemT_L`)と右オペランドの要素の型(`ElemT_R`)から変換可能な共通の型(`CommonType`)が存在すれば実行され、
`ElemT_L`と`ElemT_R`に演算が定義されている場合は演算を実行した後`CommonType`にキャストされる。
演算が定義されていない場合は`ElemT_L`および`ElemT_R`をそれぞれ`CommonType`にキャストしてから演算が実行される。

例えば、`int`と`double`の間には演算が定義されており、共通の型は`double`であるから
この二つの型の行列-行列演算は演算が実行されてから`double`にキャストされる。

```cpp
StaticMatrixBase<int, 1, 1> i = {3};
StaticMatrixBase<double, 1, 1> d = {2.9};
std::cout << i * d << std::endl;                        // static_cast<double>(3 * 2.9);
```

同様に、`int`と`std::complex<double>`の間には演算が定義されていないが、共通の型`std::complex<double>`を持ち、
`std::complex<double>`同士の演算は定義されているため、この二つの型の行列-行列演算は演算の実行前に`std::complex<double>`にキャストされる。

```cpp
StaticMatrixBase<int, 1, 1> i = {3};
StaticMatrixBase<std::complex<double>, 1, 1> cmp = {
    std::complex<double>{2.0, 2.0}
};
std::cout << i * cmp << std::endl;                      // static_cast<std::complex<double>>(3) * std::complex<double>{2.0, 2.0}
```

#### 関数呼び出し演算子

```cpp
const ElemT& operator()(const SizeT& r, const SizeT& c) const;                          // (1)
ElemT& operator()(const SizeT& r, const SizeT& c);                                      // (2)
```

- (1) r行c列の要素へ変更不可なアクセス
- (2) r行c列の要素へ変更可能なアクセス

#### 出力演算子

```cpp
std::ostream& operator<<(std::ostream& out, const StaticMatrixBase& input_matrix);      // (1)
```

- (1) 行列を出力する

### 関数

```cpp
void swap_rows(const SizeT& r1, const SizeT& r2);                                       // (1)
void swap_cols(const SizeT& c1, const SizeT& c2);                                       // (2)
```

- (1) 第`r1`行と第`r2`行を入れ替える
- (2) 第`c1`列と第`c2`列を入れ替える

行入れ替えと列入れ替えは約4倍程列入れ替えの方が遅い。