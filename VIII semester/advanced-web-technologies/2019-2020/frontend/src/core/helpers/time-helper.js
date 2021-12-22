export const timeToWords = (time, lang) => {
  lang = lang || {
    postfixes: {
      '<': ' ago',
      '>': ' from now',
    },
    1000: {
      singular: 'a few moments',
      plural: 'a few moments',
    },
    60000: {
      singular: 'about a minute',
      plural: '# minutes',
    },
    3600000: {
      singular: 'about an hour',
      plural: '# hours',
    },
    86400000: {
      singular: 'a day',
      plural: '# days',
    },
    31540000000: {
      singular: 'a year',
      plural: '# years',
    },
  };

  const timespans = [1000, 60000, 3600000, 86400000, 31540000000];

  const parsedTime = Date.parse(time.replace(/-00:?00$/, ''));

  if (parsedTime && Date.now) {
    let timeAgo = parsedTime - Date.now();
    let diff = Math.abs(timeAgo);
    let postfix = lang.postfixes[timeAgo < 0 ? '<' : '>'];
    let timespan = timespans[0];

    for (let i = 1; i < timespans.length; i++) {
      if (diff > timespans[i]) {
        timespan = timespans[i];
      }
    }

    let n = Math.round(diff / timespan);

    return lang[timespan][n > 1 ? 'plural' : 'singular'].replace('#', n) + postfix;
  }
};

// example
// let dateInWords = timeToWords(date);
