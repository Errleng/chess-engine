use num_traits::AsPrimitive;
use std::ops::{Index, IndexMut};

#[derive(Clone, Debug)]
pub struct IdxVec<T>(pub Vec<T>);

impl<T> IdxVec<T> {
    pub fn len(&self) -> usize {
        self.0.len()
    }
}

impl<T, U: AsPrimitive<usize>> Index<U> for IdxVec<T> {
    type Output = T;

    fn index(&self, index: U) -> &T {
        let idx: usize = index.as_();
        &self.0[idx]
    }
}

impl<T, U: AsPrimitive<usize>> IndexMut<U> for IdxVec<T> {
    fn index_mut(&mut self, index: U) -> &mut T {
        let idx: usize = index.as_();
        &mut self.0[idx]
    }
}

#[derive(Clone, Debug)]
pub struct FlattenedIdxVec<T> {
    pub row: usize,
    pub col: usize,
    pub cont: Vec<T>,
}

impl<T> FlattenedIdxVec<T> {
    pub fn len(&self) -> usize {
        self.cont.len()
    }
    //pub fn idx<U:AsPrimitive<usize>, V: AsPrimitive<usize>>(&self, r: U, c: V) -> &T {
    //    let idx: usize = r.as_() * self.row + c.as_();
    //    &self.cont[idx]
    //}
    //pub fn idx_mut<U:AsPrimitive<usize>, V: AsPrimitive<usize>>(&mut self, r: U, c: V) -> &mut T {
    //    let idx: usize = r.as_() * self.row + c.as_();
    //    &mut self.cont[idx]
    //}
}

impl<T, U: AsPrimitive<usize>, V: AsPrimitive<usize>> Index<(U, V)> for FlattenedIdxVec<T> {
    type Output = T;

    fn index(&self, (r, c): (U, V)) -> &T {
        let idx: usize = r.as_() * self.col + c.as_();
        &self.cont[idx]
    }
}

impl<T, U: AsPrimitive<usize>, V: AsPrimitive<usize>> IndexMut<(U, V)> for FlattenedIdxVec<T> {
    fn index_mut(&mut self, (r, c): (U, V)) -> &mut T {
        let idx: usize = r.as_() * self.col + c.as_();
        &mut self.cont[idx]
    }
}

//#[derive(Clone, Debug)]
//pub struct IdxSlice<'a, T: 'a + Clone>(pub &'a mut [T]);
//
//impl<'a, T, U: AsPrimitive<usize>> Index<U> for IdxSlice<'a, T> {
//    type Output = T;
//
//    fn index(&self, index: U) -> &T {
//        let idx: usize = index.as_();
//        &self.0[idx]
//    }
//}
//
//impl<'a, T, U: AsPrimitive<usize>> IndexMut<U> for IdxSlice<'a, T> {
//    fn index_mut(&mut self, index: U) -> &mut T {
//        let idx: usize = index.as_();
//        &mut self.0[idx]
//    }
//}
