(function (angular) {
  'use strict';
  
  function DocumentDirective ($window, $parse) {
    function DocumentCompile (tElement, tAttrs) {
      var section = angular.element(tElement.find('section')[0]);
      if (tAttrs.navMenu === 'true') {
        section.attr('class', 'col-lg-8 col-lg-offset-4 col-md-8 col-md-offset-4 col-sm-8 col-sm-offset-4');
      }
      
      return DocumentLink;
    }
    
    function DocumentLink ($scope, $element) {
      if (!$scope.navMenu) {
        return;
      }

      var sections = $element.find('section');
      $scope.navList = [];
      
      angular.forEach(sections, function (section) {
        $scope.navList.push({
            name: angular.element(section).find('h2')[0].textContent,
            id: section.id,
            selected: false
        });
      });
      
      angular.element($window).bind("scroll", function() {
        var screenTop = $window.pageYOffset,
            screenBottom = $window.innerHeight + $window.pageYOffset,
            visibleOnScreen,
            currentsection;
        
        visibleOnScreen = _.filter(sections, function (section) {
          return section.offsetTop >= screenTop && section.offsetTop < screenBottom ||
                 section.offsetTop <= screenTop && section.offsetHeight + section.offsetTop >= screenBottom;
        });

        currentsection = _.first(visibleOnScreen);
        if (currentsection) {
          $scope.navList.map(function (elem) {
            elem.selected = false;
          });
          
          var currentNavItem = _.find($scope.navList, function (navItem) {
            return navItem.id == currentsection.id;
          });
          
          currentNavItem.selected = true;
          $scope.$digest();
        }
      });
    }
    
    return {
        restrict: 'E',
        replace: true,
        transclude: true,
        scope: { navMenu: '@' },
        template: '<div class="row">' +
                  '<sc-nav nav-list="navList" class="col-lg-2 col-md-3 col-sm-3 hidden-phone menu" ng-if="navMenu">' + 
                  '</sc-nav>' + 
                  '<section ng-transclude>' +
                  '</section>' +
                '</div>',
      compile: DocumentCompile
    };
  }
  
  DocumentDirective.$inject = ['$window', '$parse'];
  
  angular.module('scDirectives').directive('scDocument', DocumentDirective);
}(angular));