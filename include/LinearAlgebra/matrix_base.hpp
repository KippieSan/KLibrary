#include "matrix_base_shape.hpp"
#include <array>
#include <cassert>
#include <iostream>
#include <concepts>

namespace linear_algebra {
    /*
     * # MatrixBaseクラス
     *
     * 基本的な行列の機能を提供するクラス
     * 
     * 
     * ## Constructor:
     * ### 引数`()`
     * デフォルトコンストラクタ
     * 全ての要素が0で初期化される。
     * 
     * ```
     * MatrixBase<int, 3, 3> m;
     * ```
     * 
     * ### 引数`(std::initializer<std::initializer<ElementType>>&&)`
     * 2次元initializer_listによるRowSize x ColumnSize行列の初期化
     * 
     * ```
     * MatrixBase<int, 3, 3> m1 = {{1, 2, 3}, {3, 4, 5}, {5, 6, 7}};
     * ```
     * 
     * ### 引数`(std::initializer<ElementType>&&)`
     * 1次元initializer_listによるRowSize x ColumnSize行列の初期化
     * 
     * ```
     * MatrixBase<int, 3, 3> m2 = {1, 2, 3, 3, 4, 5, 5, 6, 7};
     * ```
     * 
     * ### 引数`(const MatrixBase&)`
     * 左辺値MatrixBaseオブジェクトによる初期化
     * 
     * ```
     * MatrixBase<int, 3, 3> m3 = m2;
     * ```
     * 
     * ### 引数`(MatrixBase&&)`
     * 右辺値MatrixBaseオブジェクトによる初期化
     * 
     * ```
     * MatrixBase<int, 3, 3> m4 = MatrixBase<int, 3, 3>{1, 2, 3, 3, 4, 5, 5, 6, 7};
     * ```
     * 
     * ## Functions:
     * ### 代入演算子 `+=` `-=` `*=` `/=`
     * 行列-行列間もしくは行列-スカラー間の四則演算を行う。
     * 右オペランドの型が左オペランドの型に変換可能である場合に演算は定義され、
     * 左オペランドの型にキャストされたうえで演算が行われる。
     * 
     * また、乗算の行列-行列間演算は代入を行う関係上同次元の正方行列同士の掛け算に限られる。
     * 
     * 各演算子について定義される演算は以下の通り。
     * | 演算子 |行列-行列|行列-スカラー|
     * |:---:|:---:|:---:|
     * | `+=` | o | x |
     * | `-=` | o | x |
     * | `*=` | o | o |
     * | `/=` | x | o |
     * 
     * ### 四則演算子 `+` `-` `*` `/`
     * 行列-行列間もしくは行列-スカラー, スカラー-行列間の四則演算を行う。
     * 右オペランドの型と左オペランドの型がどちらか一方に変換可能である場合に演算は定義され、
     * 変換可能な型にキャストされたうえで演算が行われる。
     * 相互変換が可能な場合、サイズが大きい方の型にキャストされる。
     * 
     * 各演算子について定義される演算は以下の通り。
     * | 演算子 |行列-行列|行列-スカラー|スカラー-行列|
     * |:---:|:---:|:---:|:---:|
     * | `+` | o | x | x |
     * | `-` | o | x | x |
     * | `*` | o | o | o |
     * | `/` | x | o | x |
     * 
     * ### 出力演算子 `<<`
     * 例えば2x3行列`m`
     * 
     * ```
     * MatrixBase<int, 2, 3> m5 = {1, 2, 3, 3, 2, 1};
     * std::cout << m5 << std::endl;
     * ```
     * 
     * は以下のような形式で出力される。
     * 
     * ```text: Output
     * {1, 2, 3}
     * {3, 2, 1}
     * ```
     * 
     * ### 要素アクセス(r, c)
     * 行列の第(r, c)要素へアクセスする。
     * `const`な参照を返すものと非`const`な参照を返すものが存在し、使用法は以下の通り。
     * 
     * ```
     * MatrixBase<int, 2, 2> m6 = {1, 2, 3, 4};
     * m6(1, 1);     // const参照
     * m6(0, 1) = 5; // 非const参照
     * ```
     * 
     * ### 要素アクセス at(i)
     * 行列を管理する配列の第i要素へアクセスする。
     * 変更は許可されていない。
     * 
     * ```
     * int a = m6.at(1); // OK
     * m6.at(1) = 10;    // NG 配列要素での変更は許可されない。
     * ```
     * ### 形の取得 shape()
     * 行列の形(RowSize x ColumnSize)を取得する。
     * 返り値はMatrixBaseShape型であり、row(), column()関数を用いて各値にアクセスすることができる。
     * 
     * ```
     * m6.shape().row();
     * m6.shape().column();
     * ```
     * 
     * ## Statics:
     *      - Zeros() RowSize * ColumnSize の零行列を返す (未実装)
     *      - Ones() RowSize * ColumnSize の全ての要素が1の行列を返す (未実装)
     *      - I() n * n 単位行列を返す (未実装)
     *      - Diag(initializer_list) n * n 対角行列を返す (未実装)
     */
    template <class ElementType, std::size_t RowSize, std::size_t ColumnSize>
    class MatrixBase {
        private:
            std::array<ElementType, RowSize * ColumnSize> matrix_;
        public:
            MatrixBase() {
                this->matrix_.fill(0);
            }
            MatrixBase(std::initializer_list<std::initializer_list<ElementType>>&& input_matrix) {
                static_assert(RowSize != 0 && ColumnSize != 0);
                assert(input_matrix.size() == RowSize);
                for(const auto& row: input_matrix) {
                    assert(row.size() == ColumnSize);
                }
                
                auto matrix_iterator = this->matrix_.begin();
                for(const auto& row: input_matrix) {
                    std::move(std::begin(row), std::end(row), matrix_iterator);
                    std::advance(matrix_iterator, RowSize);
                }
            }
            MatrixBase(std::initializer_list<ElementType>&& input_matrix) {
                static_assert(RowSize != 0 && ColumnSize != 0);
                assert(input_matrix.size() == RowSize * ColumnSize);

                std::move(input_matrix.begin(), input_matrix.end(), this->matrix_.begin());
            }
            MatrixBase(const MatrixBase<ElementType, RowSize, ColumnSize>& input): matrix_(input.matrix_){}
            MatrixBase(MatrixBase<ElementType, RowSize, ColumnSize>&& input): matrix_(input.matrix_){}

            const ElementType& operator()(const std::size_t& r, const std::size_t& c) const {
                assert(r < RowSize);
                assert(c < ColumnSize);
                return this->matrix_.at(RowSize * r + c);
            }
            ElementType& operator()(const std::size_t& r, const std::size_t& c) {
                assert(r < RowSize);
                assert(c < ColumnSize);
                return this->matrix_.at(RowSize * r + c);
            }
            const ElementType& at(const std::size_t& i) const {
                assert(i < RowSize * ColumnSize);
                return this->matrix_.at(i);
            }
            constexpr MatrixBaseShape shape() const noexcept {
                return MatrixBaseShape(RowSize, ColumnSize);
            }

            template <class ElementType_R, std::size_t RowSize_R, std::size_t ColumnSize_R>
            MatrixBase& operator+=(const MatrixBase<ElementType_R, RowSize_R, ColumnSize_R>& matrix) {
                static_assert(RowSize == RowSize_R);
                static_assert(ColumnSize == ColumnSize_R);
                static_assert(std::convertible_to<ElementType_R, ElementType>);

                for(std::size_t i = 0; i < RowSize * ColumnSize; ++i) {
                    this->matrix_.at(i) += static_cast<ElementType>(matrix.at(i));
                }
                return (*this);
            }
            template <class ElementType_R, std::size_t RowSize_R, std::size_t ColumnSize_R>
            MatrixBase& operator-=(const MatrixBase<ElementType_R, RowSize_R, ColumnSize_R>& matrix) {
                static_assert(RowSize == RowSize_R);
                static_assert(ColumnSize == ColumnSize_R);
                static_assert(std::convertible_to<ElementType_R, ElementType>);

                for(std::size_t i = 0; i < RowSize * ColumnSize; ++i) {
                    this->matrix_.at(i) -= static_cast<ElementType>(matrix.at(i));
                }
                return (*this);
            }
            template <class ElementType_R, std::size_t RowSize_R, std::size_t ColumnSize_R>
            MatrixBase& operator*=(const MatrixBase<ElementType_R, RowSize_R, ColumnSize_R>& matrix) {
                static_assert(RowSize == ColumnSize);
                static_assert(RowSize_R == ColumnSize_R);
                static_assert(RowSize == RowSize_R);
                static_assert(std::convertible_to<ElementType_R, ElementType>);

                const std::size_t N = RowSize;
                MatrixBase<ElementType, RowSize, ColumnSize> result;
                for(std::size_t r = 0; r < N; ++r) {
                    for(std::size_t i = 0; i < N; ++i) {
                        for(std::size_t c = 0; c < N; ++c) {
                            result.matrix_.at(r * N + c) += (*this).at(r * N + i) * static_cast<ElementType>(matrix.at(i * N + c));
                        }
                    }
                }
                this->matrix_ = std::move(result.matrix_);
                return (*this);
            }
            template <class ScalarType>
            MatrixBase& operator*=(const ScalarType& scalar) {
                static_assert(std::convertible_to<ScalarType, ElementType>);

                for(std::size_t i = 0; i < RowSize * ColumnSize; ++i) {
                    this->matrix_.at(i) *= static_cast<ElementType>(scalar);
                }
                return (*this);
            }
            template <class ScalarType>
            MatrixBase& operator/=(const ScalarType& scalar) {
                static_assert(std::convertible_to<ScalarType, ElementType>);
                assert(scalar != ScalarType());

                for(std::size_t i = 0; i < RowSize * ColumnSize; ++i) {
                    this->matrix_.at(i) /= static_cast<ElementType>(scalar);
                }
                return (*this);
            }

            friend std::ostream& operator<<<>(std::ostream&, const MatrixBase&);
    };
    template <class ElementType, std::size_t RowSize, std::size_t ColumnSize>
    std::ostream& operator<<(std::ostream& cout, const MatrixBase<ElementType, RowSize, ColumnSize>& input_matrix) {
        const auto& matrix = input_matrix.matrix_;
        for(std::size_t r = 0; r < RowSize; ++r) {
            cout << "{ ";
            std::size_t c = 0;
            for(; c < ColumnSize - 1; ++c) {
                cout << matrix.at(RowSize * r + c) << ", ";
            }
            cout << matrix.at(RowSize * r + c) << " }" << std::endl;
        }
        return cout;
    }
}