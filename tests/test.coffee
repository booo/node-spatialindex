s = require "../index"

console.log s

rtree = new s.RTree(0.7,1000,1000,2)

console.log rtree
bounds =
  x1: 0
  y1: 0
  x2: 1
  y2: 1
console.log rtree.insertData bounds, 1
