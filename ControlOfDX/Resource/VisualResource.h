#pragma once

#include "../ControlOfDX.h"

namespace ControlOfDX
{
    using namespace System;
    using namespace System::Drawing;

    /// <summary>リソースクラス。</summary>
	public ref class VisualResource abstract
		: IDisposable
	{
#pragma region "fields"
	private:
		/// <summary>リソース名。</summary>
        String ^ name;

#pragma endregion

#pragma region "constructor/destructor"
	protected:
        /// <summary>コンストラクタ。</summary>
        /// <param name="name">リソース名。</param>
		VisualResource(String ^ name)
			: name(name)
		{}

        /// <summary>デストラクタ。</summary>
		virtual ~VisualResource() {}

        /// <summary>ファイナライザ。</summary>
		!VisualResource() {
			this->~VisualResource();
		}

    public:
        /// <summary>リソース名を取得する。</summary>
        property String ^ Name {
            String ^ get() { return this->name; }
        }

        /// <summary>デバイス依存リソースならば真を返す。</summary>
        property virtual bool IsDependent {
            bool get() { return false; }
        }

#pragma endregion

#pragma region "methods"
	public:
        /// <summary>等価判定を行う。</summary>
        /// <param name="obj">比較対象。</param>
        /// <return>等しければ真。</return>
		bool Equals(Object ^ obj) override {
			if (this->GetType()->IsInstanceOfType(obj)) {
				return this->name == ((VisualResource^)obj)->name;
			}
			else {
				return false;
			}
		}

        /// <summary>ハッシュコードを取得する。</summary>
        /// <return>ハッシュコード値。</return>
		int GetHashCode() override {
			return this->name->GetHashCode();
		}

    internal:
        /// <summary>画像リソースを使用する準備を行う。</summary>
        /// <param name="name">レンダーターゲット。</param>
        virtual void PreparationImage(ID2D1RenderTarget * renderTarget) {};

        /// <summary>リソースを使用する準備を行う。</summary>
        /// <param name="name">レンダーターゲット。</param>
        virtual void Preparation(ID2D1RenderTarget * renderTarget) = 0;

	internal:
        /// <summary>Direct2Dのインスタンスを取得する。</summary>
        virtual ID2D1Resource * GetInstance() { return NULL; }

        /// <summary>コムインターフェイスのインスタンスを取得する。</summary>
        virtual IUnknown * GetWriteInstance() { return NULL; }

        /// <summary>描画インスタンスを解放する。</summary>
        virtual void ReleaseInstance() {}

#pragma endregion
	};
}

