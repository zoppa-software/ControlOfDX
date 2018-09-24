#pragma once

namespace ControlOfDX
{
    /// <summary>1つのジオメトリオブジェクトが他のジオメトリオブジェクトと空間的にどのように関連しているかについて説明します。</summary>
    public enum class GeometryRelation
    {
        /// <summary>2つのジオメトリ間の関係は決定できません。</summary>
        GEOMETRY_RELATION_UNKNOWN = 0,

        /// <summary>2つのジオメトリは全く交差しません。</summary>
        GEOMETRY_RELATION_DISJOINT = 1,

        /// <summary>インスタンスのジオメトリは、渡されたジオメトリに完全に含まれています。</summary>
        GEOMETRY_RELATION_IS_CONTAINED = 2,

        /// <summary>インスタンスジオメトリには、渡されたジオメトリが完全に含まれます。</summary>
        GEOMETRY_RELATION_CONTAINS = 3,

        /// <summary>2つのジオメトリは重なりますが、どちらも完全には他のジオメトリを含んでいません。</summary>
        GEOMETRY_RELATION_OVERLAP = 4,

        /// <summary>無効値。</summary>
        GEOMETRY_RELATION_FORCE_DWORD = -1
    };
}