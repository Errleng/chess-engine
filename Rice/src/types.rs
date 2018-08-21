use std::ops::{Index, IndexMut};
use num_traits::AsPrimitive;

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
