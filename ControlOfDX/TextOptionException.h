#pragma once

namespace ControlOfDX
{
    using namespace System;

    /// <summary>������`��I�v�V������O�B</summary>
    public ref class TextOptionException
        : Exception
    {
    public:
        /// <summary>�f�t�H���g�R���X�g���N�^�B</summary>
        TextOptionException()
            : Exception()
        {}

        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="message">��O���b�Z�[�W�B</param>
        TextOptionException(String ^ message)
            : Exception(message)
        {}

        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="message">��O���b�Z�[�W�B</param>
        /// <param name="innerException">������O�Q�ƁB</param>
        TextOptionException(String ^ message, Exception ^ innerException)
            : Exception(message, innerException)
        {}

        /// <summary>�f�X�g���N�^�B</summary>
        virtual ~TextOptionException()
        {}
    };
}