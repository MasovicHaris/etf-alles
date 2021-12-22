export const createSortOrderFilter = ({ newestFirst, oldestFirst, ascending, descending }) => [
  // {
  //   value: 1,
  //   title: newestFirst,
  //   sortFunction: (a, b) => isBefore(new Date(a), new Date(b)),
  // },
  // {
  //   value: 2,
  //   title: oldestFirst,
  //   sortFunction: (a, b) => !isBefore(new Date(a), new Date(b)),
  // },
  {
    value: 1,
    title: ascending,
    sortFunction: (a, b) => (a !== b ? (a < b ? 1 : -1) : 0),
  },
  {
    value: 2,
    title: descending,
    sortFunction: (a, b) => (a !== b ? (a < b ? -1 : 1) : 0),
  },
];
