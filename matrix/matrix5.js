/*
 * Changes:
 * Inlined determinant (check --trace-inlining "Did not inline determinant called from main (target AST is too large [early])")
 */ 

(function(){

	function Matrix(m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44) {
		var m_matrix = [];
    	m_matrix[0] = m11; m_matrix[1] = m12; m_matrix[2] = m13; m_matrix[3] = m14; 
    	m_matrix[4] = m21; m_matrix[5] = m22; m_matrix[6] = m23; m_matrix[7] = m24; 
    	m_matrix[8] = m31; m_matrix[9] = m32; m_matrix[10] = m33; m_matrix[11] = m34; 
    	m_matrix[12] = m41; m_matrix[13] = m42; m_matrix[14] = m43; m_matrix[15] = m44;
    	this.m_matrix = m_matrix;
	}

	Matrix.prototype = { 

		mapPoint: function(p) {
			var x = this.m_matrix[12] + p.x * this.m_matrix[0] + p.y * this.m_matrix[4] + p.z * this.m_matrix[8];
			var y = this.m_matrix[13] + p.x * this.m_matrix[1] + p.y * this.m_matrix[5] + p.z * this.m_matrix[9];
			var z = this.m_matrix[14] + p.x * this.m_matrix[2] + p.y * this.m_matrix[6] + p.z * this.m_matrix[10];	
			p.x = x;
			p.y = y;
			p.z = z;		
		}
	}

	function Point(x, y, z) {
		this.x = x;
		this.y = y;
		this.z = z;
	}

	function determinant3x3(a1, a2, a3, b1, b2, b3, c1, c2, c3) {
        return a1 * (b2 * c3  - b3 * c2)
        - b1 * (a2 * c3 - a3 * c2)
        + c1 * (a2 * b3 - a3 * b2);
	}

	function determinant(matrix) {
		var m = matrix.m_matrix;
	    return m[0] * determinant3x3(m[5], m[9], m[13], m[6], m[10], m[14], m[7], m[11], m[15])
	    - m[1] * determinant3x3(m[4], m[8], m[12], m[6], m[10], m[14], m[7], m[11], m[15])
	    + m[2] * determinant3x3(m[4], m[8], m[12], m[5], m[9], m[13], m[7], m[11], m[15])
	    - m[3] * determinant3x3(m[4], m[8], m[12], m[5], m[9], m[13], m[6], m[10], m[14]);
	}

	function main() {

		var sum = 0;
		for (var i = 0; i < 10000; ++i) {
			var m = new Matrix(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16); 
			for (var j = 0; j < 10000; ++j) {
				sum+=determinant(m);
			}
			
			var p1 = new Point(1.1, 2.2, 3.3);
			for (var j = 0; j < 10000; ++j) {
				m.mapPoint(p1);
			}
		}
		//print(sum);
	}
	main();

})();