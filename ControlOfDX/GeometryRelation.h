#pragma once

namespace ControlOfDX
{
    /// <summary>1�̃W�I���g���I�u�W�F�N�g�����̃W�I���g���I�u�W�F�N�g�Ƌ�ԓI�ɂǂ̂悤�Ɋ֘A���Ă��邩�ɂ��Đ������܂��B</summary>
    public enum class GeometryRelation
    {
        /// <summary>2�̃W�I���g���Ԃ̊֌W�͌���ł��܂���B</summary>
        GEOMETRY_RELATION_UNKNOWN = 0,

        /// <summary>2�̃W�I���g���͑S���������܂���B</summary>
        GEOMETRY_RELATION_DISJOINT = 1,

        /// <summary>�C���X�^���X�̃W�I���g���́A�n���ꂽ�W�I���g���Ɋ��S�Ɋ܂܂�Ă��܂��B</summary>
        GEOMETRY_RELATION_IS_CONTAINED = 2,

        /// <summary>�C���X�^���X�W�I���g���ɂ́A�n���ꂽ�W�I���g�������S�Ɋ܂܂�܂��B</summary>
        GEOMETRY_RELATION_CONTAINS = 3,

        /// <summary>2�̃W�I���g���͏d�Ȃ�܂����A�ǂ�������S�ɂ͑��̃W�I���g�����܂�ł��܂���B</summary>
        GEOMETRY_RELATION_OVERLAP = 4,

        /// <summary>�����l�B</summary>
        GEOMETRY_RELATION_FORCE_DWORD = -1
    };
}